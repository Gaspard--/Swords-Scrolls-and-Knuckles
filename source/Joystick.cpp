#include "Joystick.hpp"
#include <iostream>

/// Singleton
std::vector<std::unique_ptr<Joystick>> Joystick::joystickInstances;

std::vector<std::unique_ptr<Joystick>> &Joystick::getJoysticks(void)
{
  return (joystickInstances);
}

// Default constructor
Joystick::Joystick(void)
  : Input<OIS::JoyStick, OIS::JoyStickListener>()
{}

bool Joystick::buttonPressed(OIS::JoyStickEvent const &arg, int button)
{
  states[static_cast<joystickState>(button + 1)] = true;
  try
  {
    return (statesCallbacks.at(static_cast<joystickState>(button + 1))(false));
  }
  catch (std::out_of_range const &) {}
  return (true);
}

bool Joystick::buttonReleased(OIS::JoyStickEvent const &arg, int button)
{
  states[static_cast<joystickState>(button + 1)] = false;
  try
  {
    return (statesCallbacks.at(static_cast<joystickState>(button + 1))(true));
  }
  catch (std::out_of_range const &) {}
  return (true);
}

bool Joystick::axisMoved(const OIS::JoyStickEvent &arg, int axis)
{
  axes[LEFT_HRZ] = (arg.state.mAxes[0].abs * 100) / 32767;
  axes[LEFT_VRT] = (arg.state.mAxes[1].abs * 100) / 32767;
  axes[LEFT_TOP] = (arg.state.mAxes[2].abs * 100) / 32767;
  axes[RIGHT_HRZ] = (arg.state.mAxes[3].abs * 100) / 32767;
  axes[RIGHT_VRT] = (arg.state.mAxes[4].abs * 100) / 32767;
  axes[RIGHT_TOP] = (arg.state.mAxes[5].abs * 100) / 32767;
  states[JS_LLEFT] = arg.state.mAxes[0].abs < -10000;
  states[JS_LRIGHT] = arg.state.mAxes[0].abs > 10000;
  states[JS_LUP] = arg.state.mAxes[1].abs < -10000;
  states[JS_LDOWN] = arg.state.mAxes[1].abs > 10000;
  states[JS_LT] = (arg.state.mAxes[2].abs > -25000 && arg.state.mAxes[2].abs != 0);
  states[JS_RLEFT] = arg.state.mAxes[3].abs < -10000;
  states[JS_RRIGHT] = arg.state.mAxes[3].abs > 10000;
  states[JS_RUP] = arg.state.mAxes[4].abs < -10000;
  states[JS_RDOWN] = arg.state.mAxes[4].abs > 10000;
  states[JS_RT] = (arg.state.mAxes[5].abs > -25000 && arg.state.mAxes[5].abs != 0);
  return (true);
}

void Joystick::registerCallback(joystickState state, std::function<bool(bool)> const &fn)
{
  statesCallbacks[state] = fn;
}

void Joystick::clearCallbacks(void)
{
  states.clear();
}

bool Joystick::isStateUp(joystickState js) const
{
  return (states.at(js));
}

std::map<joystickAxe, int> &Joystick::getAxes(void)
{
  return (axes);
}

bool Joystick::operator[](joystickState js)
{
  return (isStateUp(js));
}
