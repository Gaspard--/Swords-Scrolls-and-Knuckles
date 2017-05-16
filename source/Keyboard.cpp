#include <iostream>
#include "Keyboard.hpp"

/// Singleton

Keyboard Keyboard::keyboardInstance;

Keyboard &Keyboard::getKeyboard(void)
{
  return (keyboardInstance);
}

Keyboard::KeyboardKey Keyboard::getKeys(void) {
  return (KeyboardKey());
}

/// Default constructor

Keyboard::Keyboard(void)
  : Input<OIS::Keyboard>()
{}

// Protected functions

bool Keyboard::keyPressed(OIS::KeyEvent const &ke) {
  return (true);
}

bool Keyboard::keyReleased(OIS::KeyEvent const &ke) {
  return (true);
}

// Keys

bool Keyboard::KeyboardKey::operator[](OIS::KeyCode &&kc) {
  return (Keyboard::getKeyboard()->isKeyDown(kc));
}
