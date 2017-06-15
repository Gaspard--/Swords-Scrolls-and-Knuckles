#include "SceneMainMenu.hpp"
#include "Game.hpp"
#include "Mouse.hpp"

SceneMainMenu::SceneMainMenu(Renderer &r)
  : uiMenu(r)
{
  Keyboard::getKeyboard().registerCallback(OIS::KC_ESCAPE, [](bool b) {
    if (!b) {
      throw Game::GameQuitException();
    }
  });
  Mouse::getMouse().registerCallback(OIS::MouseButtonID::MB_Left, [this](OIS::MouseEvent const &e) {
    uiMenu.mousePressed(
      static_cast<Ogre::Real>(e.state.X.abs),
      static_cast<Ogre::Real>(e.state.Y.abs)
    );
  });
}

bool SceneMainMenu::update(Game &, Ogre::FrameEvent const &) {
  return (true);
}
