#include <functional>
#include <memory>
#include <stdexcept>
#include "Game.hpp"
#include "SceneStart.hpp"
#include "Joystick.hpp"
#include "PyPlugin.hpp"
#include "LevelScene.hpp"

// Constructor

Game::Game()
  : root(Game::PLUGINS_CONFIG_PATH)
  , window(nullptr)
  , inputManager(nullptr)
{
  setupResources();
  setupRenderSystem();

  // Create the window
  window = root.initialise(true, "Swords, Scrolls and Knuckles");

  // Set up keyboard / mouse handlers
  setupOIS();

  // Set up the renderer
  renderer.reset(new Renderer(*this));

  // Load resources
  Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
  Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

  root.addFrameListener(this);

  // Font loading
  Ogre::FontPtr font = Ogre::FontManager::getSingletonPtr()->getByName("HUD/Font");
  font->load();

  // Activate vsync
  window->setVSyncEnabled(true);

  // Go to start screen
  renderer->doSwitchScene(Renderer::SceneSwitcherException([this]() {
    return (static_cast<Scene *>(new SceneStart(*renderer)));
  }));

  // Loading wall mesh
  LevelScene::createWallMesh();

  // Adding the joysticks
  for (size_t i = 0; i < 4; i++)
    addJoystick(i);

  Py_Initialize();
  PyPlugin::pybind11_init();
}

Game::~Game(void)
{
  if (window != nullptr) {
    Ogre::WindowEventUtilities::removeWindowEventListener(window, this);
    windowClosed(window);
  }
}

// Private functions

void Game::setupResources(void) {
  // Load resources paths from config file.
  Ogre::ConfigFile cf;
  cf.load(Game::RESOURCES_CONFIG_PATH);
  Ogre::String name;
  Ogre::String locType;

  Ogre::ConfigFile::SectionIterator secIt = cf.getSectionIterator();
  while (secIt.hasMoreElements())
    for (auto &&pair : *secIt.getNext())
    {
      locType = pair.first;
      name = pair.second;
      Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, locType);
    }
}

void Game::setupRenderSystem(void) {
  // Look for the OpenGL render system
  for (auto const &rs : root.getAvailableRenderers()) {
    if (rs->getName().find("OpenGL") != std::string::npos) {
      root.setRenderSystem(rs);
      rs->setConfigOption("Full Screen", "Yes");
      rs->setConfigOption("Video Mode",
	std::to_string(Game::WIDTH) + " x " + std::to_string(Game::HEIGHT)
	+ " @ 32-bit colour");
      return;
    }
  }
  throw SetupException("Can't find an available Renderer");
}

void Game::setupOIS(void) {
  OIS::ParamList pl;
  size_t windowHnd;
  std::ostringstream stream;

  windowHnd = 0;
  window->getCustomAttribute("WINDOW", &windowHnd);
  stream << windowHnd;
  pl.insert(std::make_pair(std::string("WINDOW"), stream.str()));

#if defined OIS_WIN32_PLATFORM
  pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND")));
  pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
  pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
  pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
#elif defined OIS_LINUX_PLATFORM
  pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
  pl.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
  pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
  pl.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
#endif

  inputManager = OIS::InputManager::createInputSystem(pl);
  Ogre::WindowEventUtilities::addWindowEventListener(window, this);

  Keyboard::getKeyboard().init(OIS::OISKeyboard, inputManager);
  Mouse::getMouse().init(OIS::OISMouse, inputManager);
  OIS::MouseState const &ms = Mouse::getMouse()->getMouseState();
  ms.width = Game::WIDTH;
  ms.height = Game::HEIGHT;
}

bool Game::addJoystick(size_t i)
{
  try
  {
    std::unique_ptr<Joystick> newJoystick(new Joystick(i));
    newJoystick->init(OIS::OISJoyStick, inputManager);
    Joystick::getJoysticks()[i] = std::move(newJoystick);
    if (renderer->getScene())
      renderer->getScene()->resetSceneCallbacks(*renderer);
    return (true);
  }
  catch (std::exception const &) {}
  return (false);
}

// Protected functions

bool Game::frameRenderingQueued(Ogre::FrameEvent const &fe) {
  bool go_on = true;

  if (window->isClosed())
    return (false);

  try
  {
    // Need to capture / update each device
    Keyboard::getKeyboard()->capture();
    Mouse::getMouse()->capture();
    for (auto &it : Joystick::getJoysticks())
    {
      if (it != nullptr)
	(*it)->capture();
    }

    // Update the current scene's logic
    if (renderer->getScene()) {
      go_on &= renderer->getScene()->update(*this, fe);
    }
  }
  catch (Renderer::SceneSwitcherException const &sse) {
    renderer->doSwitchScene(sse);
  }
  return (go_on);
}

void Game::windowClosed(Ogre::RenderWindow* rw)
{
  if (rw == window)
  {
    if (inputManager)
    {
      Keyboard::getKeyboard().destroy(inputManager);
      Mouse::getMouse().destroy(inputManager);
      OIS::InputManager::destroyInputSystem(inputManager);
      inputManager = nullptr;
    }
  }
}

void Game::windowResized(Ogre::RenderWindow* rw)
{
  if (rw == window) {
    rw->resize(Game::WIDTH, Game::HEIGHT);
  }
}

// Public functions

void Game::run(void) {
  root.startRendering();
}

Ogre::Root &Game::getRoot(void) {
  return (root);
}

Ogre::Root const &Game::getRoot(void) const {
  return (root);
}

Ogre::RenderWindow &Game::getWindow(void) {
  return (*window);
}

Ogre::RenderWindow const &Game::getWindow(void) const {
  return (*window);
}

Renderer &Game::getRenderer(void) {
  return (*renderer);
}

Renderer const &Game::getRenderer(void) const {
  return (*renderer);
}
