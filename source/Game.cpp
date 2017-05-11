#include <stdexcept>
#include "Game.hpp"

char const *const Game::PLUGINS_CONFIG_PATH = "plugins.cfg";
char const *const Game::RESOURCES_CONFIG_PATH = "resources.cfg";

Game::Game(void)
  : _root()
  , _window(nullptr)
{}

Game::~Game(void)
{}

void Game::setup(void) {
  // Add a call to the SaveManager to load the last save.
  // Add code to load primordial game resources
}

void Game::run(void) {
  setup();
}

