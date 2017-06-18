#include "SceneSelection.hpp"
#include "Game.hpp"
#include "Mouse.hpp"

SceneSelection::SceneSelection(Renderer &r)
  : uiSelection(r)
{}
 
void SceneSelection::resetSceneCallbacks(Renderer &r) {
  auto const changeSkinUp([this, &r](bool b, size_t = 0) {
    if (!b) {
      uiSelection.changeSkin(r, true);
    }
  });
  auto const changeSkinDown([this, &r](bool b, size_t = 0) {
    if (!b) {
      uiSelection.changeSkin(r, false);
    }
  });
  auto const changeSelectionUp([this](bool b, size_t = 0) {
    if (!b) {
      uiSelection.changeSelection(true);
    }
  });
  auto const changeSelectionDown([this](bool b, size_t = 0) {
    if (!b) {
      uiSelection.changeSelection(false);
    }
  });
  auto const changeGameplayUp([this](bool b, size_t = 0) {
    if (!b) {
      uiSelection.changeGameplay(true);
    }
  });
  auto const changeGameplayDown([this](bool b, size_t = 0) {
    if (!b) {
      uiSelection.changeGameplay(false);
    }
  });

  InputCallbacks::clearAllCallbacks();
  uiSelection.resetUICallbacks();
  Keyboard::getKeyboard().registerCallback(OIS::KC_SPACE, changeSkinUp);
  Keyboard::getKeyboard().registerCallback(OIS::KC_UP, changeGameplayUp);
  Keyboard::getKeyboard().registerCallback(OIS::KC_DOWN, changeGameplayDown);
  Keyboard::getKeyboard().registerCallback(OIS::KC_LEFT, changeSelectionDown);
  Keyboard::getKeyboard().registerCallback(OIS::KC_RIGHT, changeSelectionUp);
  Joystick::registerGlobalCallback(joystickState::JS_RT, changeSkinUp);
  Joystick::registerGlobalCallback(joystickState::JS_LT, changeSkinDown);
  Joystick::registerGlobalCallback(joystickState::JS_RUP, changeGameplayUp);
  Joystick::registerGlobalCallback(joystickState::JS_RDOWN, changeGameplayDown);
  Joystick::registerGlobalCallback(joystickState::JS_RLEFT, changeSelectionDown);
  Joystick::registerGlobalCallback(joystickState::JS_RRIGHT, changeSelectionUp);
}

bool SceneSelection::update(Game &, Ogre::FrameEvent const &fe) {
  uiSelection.updateUI(fe.timeSinceLastFrame);
  return (true);
}
