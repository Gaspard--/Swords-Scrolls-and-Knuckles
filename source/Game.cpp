#include <memory>
#include <stdexcept>
#include "Game.hpp"
#include "DemoScene.hpp"

// Constructors

Game::Game(void)
  : root(Game::PLUGINS_CONFIG_PATH)
  , window(nullptr)
  , inputManager(nullptr)
{}

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

  Ogre::ConfigFile::SectionIterator secIt= cf.getSectionIterator();
  while (secIt.hasMoreElements())
  {
    Ogre::ConfigFile::SettingsMultiMap* settings = secIt.getNext();
    Ogre::ConfigFile::SettingsMultiMap::iterator it;
    for (it = settings->begin(); it != settings->end(); ++it)
    {
      locType = it->first;
      name = it->second;
      Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, locType);
    }
  }
}

void Game::setupRenderSystem(void) {
  // Look for the OpenGL render system
  auto const &rlist = root.getAvailableRenderers();

  for (auto const &rs : rlist) {
    if (rs->getName().find("OpenGL") != std::string::npos) {
      root.setRenderSystem(rs);
      rs->setConfigOption("Full Screen", "Yes");
      rs->setConfigOption("Video Mode", "1920 x 1080 @ 32-bit colour");
      return ;
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

  inputManager = OIS::InputManager::createInputSystem(pl);
  Ogre::WindowEventUtilities::addWindowEventListener(window, this);

  Keyboard::getKeyboard().init(OIS::OISKeyboard, inputManager);
}

// Protected functions

bool Game::frameRenderingQueued(Ogre::FrameEvent const &event) {
  bool go_on = true;

  if (window->isClosed())
    return (false);

  // Need to capture / update each device
  Keyboard::getKeyboard()->capture();

  // Update the current scene's logic
  if (renderer->getScene()) {
    go_on &= renderer->getScene()->update(*this);
  }

  if (Keyboard::getKeys()[OIS::KC_ESCAPE])
    go_on = false;
  return (go_on);
}

void Game::windowClosed(Ogre::RenderWindow* rw)
{
  if (rw == window)
  {
    if (inputManager)
    {
      Keyboard::getKeyboard().destroy(inputManager);
      OIS::InputManager::destroyInputSystem(inputManager);
      inputManager = nullptr;
    }
  }
}

// Public functions

void Game::setup(void) {
  setupResources();
  setupRenderSystem();

  // Create the window
  window = root.initialise(true, "Swords, Scrolls and Knuckles");

  // Load resources
  Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
  Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

  // Set up keyboard / mouse handlers
  setupOIS();

  // Set up the renderer and initial scene
  renderer.reset(new Renderer(*this));
  renderer->switchScene(*this, std::unique_ptr<Scene>(new DemoScene()));

  root.addFrameListener(this);
}

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
