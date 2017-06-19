#include "SceneMainMenu.hpp"
#include "SceneScoreboard.hpp"

SceneScoreboard::SceneScoreboard(Renderer &r)
  : uiScoreboard(r)
{}

void SceneScoreboard::resetSceneCallbacks(Renderer &renderer) {
  InputCallbacks::clearAllCallbacks();
  uiScoreboard.resetUICallbacks();
  Keyboard::getKeyboard().registerCallback(OIS::KC_ESCAPE, [&renderer](bool b) {
    if (!b) {
      renderer.switchScene([&renderer]() {
        return static_cast<Scene *>(new SceneMainMenu(renderer));
      });
    }
  });
}
