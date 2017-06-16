#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "Joystick.hpp"

void InputCallbacks::clearAllCallbacks(void) {
  Keyboard::getKeyboard().clearCallbacks();
  Mouse::getMouse().clearCallbacks();
  Joystick::clearGlobalCallbacks();
}
