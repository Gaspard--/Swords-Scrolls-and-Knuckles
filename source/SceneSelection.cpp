#include "SceneSelection.hpp"
#include "Game.hpp"
#include "Mouse.hpp"

SceneSelection::SceneSelection(Renderer &r)
  : uiSelection(r)
{}
 
void SceneSelection::resetSceneCallbacks(void) {
  InputCallbacks::clearAllCallbacks();
  uiSelection.resetUICallbacks();
  Keyboard::getKeyboard().registerCallback(OIS::KC_UP, [](bool b) {
    if (!b) {

    }
  });
}

bool SceneSelection::update(Game &, Ogre::FrameEvent const &fe) {
  uiSelection.updateUI(fe.timeSinceLastFrame);
  return (true);
}
