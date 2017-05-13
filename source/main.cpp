#include <exception>
#include "Game.hpp"

int main() {
  try {
    Game::getSingleton().setup();
    Game::getSingleton().run();
    return (0);
  }
  catch (Game::SetupException const &e) {
    std::cerr << "Failed to setup game: " << e.what() << std::endl;
  }
  catch (Ogre::Exception const &e) {
    std::cerr << "An exception has occured and SSK has stopped: " << e.getFullDescription() << std::endl;
  }
  catch (std::exception const &e) {
    std::cerr << "An unknown exception has occured: " << e.what() << std::endl;
  }
  return (1);
}
