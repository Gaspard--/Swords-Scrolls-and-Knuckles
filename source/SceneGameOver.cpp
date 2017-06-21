#include "SceneGameOver.hpp"
#include "Game.hpp"
#include "Mouse.hpp"

SceneGameOver::SceneGameOver(Renderer &renderer)
  : uiMenu(renderer)
{
}

void SceneGameOver::resetSceneCallbacks(Renderer &) {
  InputCallbacks::clearAllCallbacks();
  uiMenu.resetUICallbacks();
  Keyboard::getKeyboard().registerCallback(OIS::KC_ESCAPE, [](bool b) {
    if (!b) {
      throw Game::GameQuitException();
    }
  });
}
