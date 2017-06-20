#include "SceneOptions.hpp"

SceneOptions::SceneOptions(Renderer &r)
  : uiOptions(r)
{}

void SceneOptions::resetSceneCallbacks(Renderer &r) {
  InputCallbacks::clearAllCallbacks();
  uiOptions.resetUICallbacks();
}
