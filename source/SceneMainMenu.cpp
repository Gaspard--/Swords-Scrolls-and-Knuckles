#include "SceneMainMenu.hpp"
#include "Game.hpp"
#include "Mouse.hpp"

SceneMainMenu::SceneMainMenu(Renderer &r)
  : uiMenu(r)
{}

void SceneMainMenu::resetSceneCallbacks(Renderer &) {
  InputCallbacks::clearAllCallbacks();
  uiMenu.resetUICallbacks();
  Keyboard::getKeyboard().registerCallback(OIS::KC_ESCAPE, [](bool b) {
    if (!b) {
      throw Game::GameQuitException();
    }
  });
}

bool SceneMainMenu::update(Game &, Ogre::FrameEvent const &) {
  return (true);
}
