#include "SceneSelection.hpp"
#include "Game.hpp"
#include "Mouse.hpp"

SceneSelection::SceneSelection(Renderer &r)
  : uiSelection(r)
{}
 
void SceneSelection::resetSceneCallbacks(void) {
  InputCallbacks::clearAllCallbacks();
  uiSelection.resetUICallbacks();
}

bool SceneSelection::update(Game &, Ogre::FrameEvent const &) {
  return (true);
}
