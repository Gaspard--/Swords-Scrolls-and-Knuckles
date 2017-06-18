#include "Joystick.hpp"
#include <iostream>

/// Singleton
std::array<std::unique_ptr<Joystick>, 4> Joystick::joystickInstances;

std::array<std::unique_ptr<Joystick>, 4> &Joystick::getJoysticks(void)
{
  return (joystickInstances);
}

void Joystick::registerGlobalCallback(joystickState state, std::function<void(bool, size_t)> const &fn) {
  for (auto const &js : joystickInstances) {
    if (js) {
      js->registerCallback(state, fn);
    }
  }
}

void Joystick::clearGlobalCallbacks(void) {
  for (auto const &js : joystickInstances) {
    if (js) {
      js->clearCallbacks();
    }
  }
}

// Default constructor
Joystick::Joystick(size_t i)
  : Input<OIS::JoyStick, OIS::JoyStickListener>()
  , idx(i)
{}

bool Joystick::buttonPressed(OIS::JoyStickEvent const &, int button)
{
  std::cout << "Button :" << button << std::endl;
  states[static_cast<joystickState>(button + 1)] = true;
  try
  {
    statesCallbacks.at(static_cast<joystickState>(button + 1))(false, idx);
  }
  catch (std::out_of_range const &) {}
  return (true);
}

bool Joystick::buttonReleased(OIS::JoyStickEvent const &, int button)
{
  states[static_cast<joystickState>(button + 1)] = false;
  try
  {
    statesCallbacks.at(static_cast<joystickState>(button + 1))(true, idx);
  }
  catch (std::out_of_range const &) {}
  return (true);
}

bool Joystick::axisMoved(const OIS::JoyStickEvent &arg, int)
{
  auto const calcAxes([&arg](int i)
  {
    return ((arg.state.mAxes[i].abs * 100) / 32767);
  });
  auto const updateCallbacks([this, &arg](joystickAxe axe, joystickState a, joystickState b) {
    if (axes[axe] < -90)
    {
      states[a] += (states[a] < 2);
      states[b] = 0;
      if (states[a] == 1) {
	try {
	  statesCallbacks.at(a)(false, idx);
	}
	catch (std::out_of_range const &) {}
      }
    }
    else if (axes[axe] > 90) {
      states[b] += (states[b] < 2);
      states[a] = 0;
      if (states[b] == 1) {
	try {
	  statesCallbacks.at(b)(false, idx);
	}
	catch (std::out_of_range const &) {}
      }
    }
    else {
      states[a] = 0;
      states[b] = 0;
    }
  });
  axes[LEFT_VRT] = calcAxes(0);
  axes[LEFT_HRZ] = calcAxes(1);
  axes[RIGHT_VRT] = calcAxes(2);
  axes[RIGHT_HRZ] = calcAxes(3);
  updateCallbacks(LEFT_VRT, JS_LUP, JS_LDOWN);
  updateCallbacks(LEFT_HRZ, JS_LRIGHT, JS_LLEFT);
  updateCallbacks(RIGHT_VRT, JS_RUP, JS_RDOWN);
  updateCallbacks(RIGHT_HRZ, JS_RLEFT, JS_RRIGHT);

  /*
  TODO: verify these axes too

  axes[LEFT_TOP] = calcAxes(2);
  axes[RIGHT_TOP] = calcAxes(5);
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
  */
  return (true);
}

void Joystick::registerCallback(joystickState state, std::function<void(bool, size_t)> const &fn)
{
  statesCallbacks[state] = fn;
}

void Joystick::clearCallbacks(void)
{
  statesCallbacks.clear();
}

bool Joystick::isStateUp(joystickState js) const
{
  return (states.at(js));
}

std::map<joystickAxe, int> &Joystick::getAxes(void)
{
  return (axes);
}

std::map<joystickAxe, int> const &Joystick::getAxes(void) const
{
  return (axes);
}

bool Joystick::operator[](joystickState js) const
{
  return (isStateUp(js));
}
