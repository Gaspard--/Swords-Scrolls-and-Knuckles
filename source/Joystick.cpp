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
    std::cout << "=========================" << std::endl;
    std::cout << "BUTTON PRESSED: " << button << std::endl;
    std::cout << "mButtons:" << std::endl << std::boolalpha;
    for (auto it = arg.state.mButtons.begin(); it < arg.state.mButtons.end(); it++)
    {
        std::cout << *it << std::endl;
    }
    states[static_cast<joystickState>(button + 1)] = true;
    if (!button)
    {
        std::cout << "STATES:" << std::endl << std::boolalpha;
        for (auto it = states.begin(); it != states.end(); it++)
        {
            std::cout << it->first << ": " << static_cast<bool>(it->second) << std::endl;
        }
    }
    return (true);
}

bool Joystick::buttonReleased(OIS::JoyStickEvent const &arg, int button)
{
    states[static_cast<joystickState>(button + 1)] = false;
    return (true);
}

bool Joystick::axisMoved(const OIS::JoyStickEvent &arg, int axis)
{
    if ((arg.state.mAxes[axis].abs > 10000 || arg.state.mAxes[axis].abs < -10000) && false)
    {
        std::cout << "=========================" << std::endl;
        std::cout << "AXIS MOVED: " << axis << std::endl;
        std::cout << "mAxes:" << std::endl;
        for (auto it = arg.state.mAxes.begin(); it < arg.state.mAxes.end(); it++)
        {
            std::cout << (*it).abs << std::endl;
        }
    }
    axes[LEFT_HRZ] = (arg.state.mAxes[0].abs * 100) / 32767;
    axes[LEFT_VRT] = (arg.state.mAxes[1].abs * 100) / 32767;
    axes[LEFT_TOP] = (arg.state.mAxes[2].abs * 100) / 32767;
    axes[RIGHT_HRZ] = (arg.state.mAxes[3].abs * 100) / 32767;
    axes[RIGHT_VRT] = (arg.state.mAxes[4].abs * 100) / 32767;
    axes[RIGHT_TOP] = (arg.state.mAxes[5].abs * 100) / 32767;
    states[static_cast<joystickState>(12)] = arg.state.mAxes[0].abs < -10000;
    states[static_cast<joystickState>(13)] = arg.state.mAxes[0].abs > 10000;
    states[static_cast<joystickState>(14)] = arg.state.mAxes[1].abs < -10000;
    states[static_cast<joystickState>(15)] = arg.state.mAxes[1].abs > 10000;
    states[static_cast<joystickState>(16)] = arg.state.mAxes[2].abs > -25000 && arg.state.mAxes[2].abs != 0;
    states[static_cast<joystickState>(17)] = arg.state.mAxes[3].abs < -10000;
    states[static_cast<joystickState>(18)] = arg.state.mAxes[3].abs > 10000;
    states[static_cast<joystickState>(19)] = arg.state.mAxes[4].abs < -10000;
    states[static_cast<joystickState>(20)] = arg.state.mAxes[4].abs > 10000;
    states[static_cast<joystickState>(21)] = arg.state.mAxes[5].abs > -25000 && arg.state.mAxes[5].abs != 0;
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

bool Joystick::isStateUp(joystickState js)
{
  return (states[js]);
}

std::map<joystickAxe, int> &Joystick::getAxes(void)
{
  return (axes);
}

bool Joystick::operator[](joystickState js)
{
  return (isStateUp(js));
}
