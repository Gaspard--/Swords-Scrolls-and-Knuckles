#include "SceneStart.hpp"
#include "Game.hpp"
#include "Mouse.hpp"

SceneStart::SceneStart(Renderer &renderer)
  : uiMenu(renderer)
{
}

void SceneStart::resetSceneCallbacks(Renderer &renderer) {
  InputCallbacks::clearAllCallbacks();
  uiMenu.resetUICallbacks();
  Keyboard::getKeyboard().registerCallback(OIS::KC_SPACE, [&renderer](bool b) {
    if (!b) {
		  renderer.switchScene([&renderer]() {
      return static_cast<Scene *>(new SceneMainMenu(renderer));
    });
    }
  });
}

bool SceneStart::update(Game &, Ogre::FrameEvent const &) {
  
  uiMenu.update();
  return (true);
}
