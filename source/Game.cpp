#include <memory>
#include <stdexcept>
#include "Game.hpp"
#include "DemoScene.hpp"

char const *const Game::PLUGINS_CONFIG_PATH = "resources/cfg/plugins.cfg";
char const *const Game::RESOURCES_CONFIG_PATH = "resources/cfg/resources.cfg";

Game Game::gameInstance;

// Singleton

Game &Game::getSingleton(void)
{
  return (gameInstance);
}

// Constructors

Game::Game(void)
  : _root(Game::PLUGINS_CONFIG_PATH)
{}

Game::~Game(void)
{}

// Private functions

void Game::setupResources(void) {
  // Load resources paths from config file.
  Ogre::ConfigFile cf;
  cf.load(Game::RESOURCES_CONFIG_PATH);

  auto const &sections = cf.getSettingsBySection();
  for (auto const &it : sections) {
    for (auto const &it2 : it.second) {
      Ogre::ResourceGroupManager::getSingleton()
	.addResourceLocation(it2.second, it2.first, it.first);
    }
  }
}

void Game::setupRenderSystem(void) {
  // Look for the OpenGL render system
  auto const &rlist = _root.getAvailableRenderers();

  for (auto const &rs : rlist) {
    if (rs->getName().find("OpenGL") != std::string::npos) {
      _root.setRenderSystem(rs);
      rs->setConfigOption("Full Screen", "Yes");
      rs->setConfigOption("Video Mode", "1920 x 1080 @ 32-bit colour");
      return ;
    }
  }
  throw SetupException("Can't find an available Renderer");
}

// Public functions

void Game::setup(void) {
  setupResources();
  setupRenderSystem();

  // Create the window
  _window = _root.initialise(true, "Swords, Scrolls and Knuckles");

  // Load resources
  Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
  Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

  // Set up the renderer and initial scene
  _renderer.reset(new Renderer());
  _renderer->switchScene(std::unique_ptr<Scene>(new DemoScene()));
}

void Game::run(void) {
  setup();
  while (42) {
    Ogre::WindowEventUtilities::messagePump();

    if (_window->isClosed() || !_root.renderOneFrame())
      break;
  }
}

Ogre::Root &Game::getRoot(void) {
  return (_root);
}

Ogre::Root const &Game::getRoot(void) const {
  return (_root);
}

Ogre::RenderWindow &Game::getWindow(void) {
  return (*_window);
}

Ogre::RenderWindow const &Game::getWindow(void) const {
  return (*_window);
}

Renderer &Game::getRenderer(void) {
  return (*_renderer);
}

Renderer const &Game::getRenderer(void) const {
  return (*_renderer);
}
