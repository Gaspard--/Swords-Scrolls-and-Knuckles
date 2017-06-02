#include <memory>
#include <stdexcept>
#include "Game.hpp"
#include "DemoScene.hpp"
#include "UIManager.hpp"

// Constructors

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
  
  // Init scene
  renderer->switchScene([this](){
      return new DemoScene(*this);
    });
  root.addFrameListener(this);
   
  // Init UIManager
  UIManager *manager = new UIManager();
  // manager->showOverlayByName("hud");
  manager->showOverlayByName("menu");
  // static_cast<UIOverlayHUD *>(manager->getByName("hud"))->updateScoreByName("Wizzard", 25);
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
      // rs->setConfigOption("Video Mode", "1920 x 1080 @ 32-bit colour");
	  rs->setConfigOption("Video Mode",
			  std::to_string(Game::WIDTH) + " x " + std::to_string(Game::HEIGHT)
			  + " @ 32-bit colour");
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
