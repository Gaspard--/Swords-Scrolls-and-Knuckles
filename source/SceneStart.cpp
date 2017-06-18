#include "SceneStart.hpp"
#include "Game.hpp"
#include "Mouse.hpp"

SceneStart::SceneStart(Renderer &renderer)
  : uiMenu(renderer)
{
}

void SceneStart::resetSceneCallbacks(Renderer &renderer) {
  auto const gotoMainMenu([&renderer](bool b, size_t i = 0) {
    if (!b) {
      renderer.switchScene([&renderer]() {
	return static_cast<Scene *>(new SceneMainMenu(renderer));
      });
    }
  });
  InputCallbacks::clearAllCallbacks();
  uiMenu.resetUICallbacks();
  Keyboard::getKeyboard().registerCallback(OIS::KC_SPACE, gotoMainMenu);
  Joystick::registerGlobalCallback(joystickState::JS_A, gotoMainMenu);
}

bool SceneStart::update(Game &, Ogre::FrameEvent const &) {
  uiMenu.update();
  return (true);
}
