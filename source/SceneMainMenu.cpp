#include "SceneMainMenu.hpp"
#include "Game.hpp"
#include "Mouse.hpp"

SceneMainMenu::SceneMainMenu(Renderer &r)
  : uiMenu(r)
{
  Keyboard::getKeyboard().registerCallback(OIS::KC_ESCAPE, [](bool b) {
    if (!b) {
      throw Game::GameQuitException("Leaving game");
    }
  });
  Mouse::getMouse().registerMouseMoveCallback([this](Ogre::Real x, Ogre::Real y) {
    uiMenu.mouseMoved(x, y);
  });
  Mouse::getMouse().registerCallback(OIS::MouseButtonID::MB_Left, [this](OIS::MouseEvent const &e) {
    uiMenu.mousePressed(
      static_cast<Ogre::Real>(e.state.X.abs),
      static_cast<Ogre::Real>(e.state.Y.abs)
    );
  });
}

bool SceneMainMenu::update(Game &g, Ogre::FrameEvent const &fe) {
  return (true);
}
