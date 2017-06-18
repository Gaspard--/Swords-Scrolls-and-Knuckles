#ifndef ACTION_HPP_
# define ACTION_HPP_

#include <map>
#include "Joystick.hpp"
#include "KeyboardController.hpp"
#include "Keyboard.hpp"

class Player;

class Action
{
public:
  std::map<Joystick *, Player *> joystickControlled;
  std::map<KeyboardController *, Player *> keyboardControlled;

public:
  Action() = default;
  ~Action() = default;

public:
  void update();
};

#endif // !ACTION_HPP_
