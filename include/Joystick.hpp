#ifndef JOYSTICK_HPP_
# define JOYSTICK_HPP_

# include <functional>
# include <OISJoyStick.h>
# include "Input.hpp"

enum joystickState
{
    JS_UNASSIGNED = 0x00,
    JS_A = 0x01,
    JS_B = 0x02,
    JS_X = 0x03,
    JS_Y = 0x04,
    JS_LB = 0x05,
    JS_RB = 0x06,
    JS_SELECT = 0x07,
    JS_START = 0x08,
    JS_MENU = 0x09,
    JS_LJS = 0x0A,
    JS_RJS = 0x0B,
    JS_LLEFT = 0x0C,
    JS_LRIGHT = 0x0D,
    JS_LUP = 0x0E,
    JS_LDOWN = 0x0F,
    JS_LT = 0x10,
    JS_RLEFT = 0x11,
    JS_RRIGHT = 0x12,
    JS_RUP = 0x13,
    JS_RDOWN = 0x14,
    JS_RT = 0x15,
};

class Joystick : public Input<OIS::JoyStick, OIS::JoyStickListener>
{
    std::map<joystickState, std::function<bool(bool)>> statesCallbacks;
    std::map<joystickState, bool> states;

    /// Singleton instance
    static Joystick joystickInstance;

    /// Private constructor (Singleton)
    Joystick(void);

  protected:
    /// OIS::JoyStickListener
    virtual bool buttonPressed(OIS::JoyStickEvent const &arg, int button) override;
    virtual bool buttonReleased(OIS::JoyStickEvent const &arg, int button) override;
    virtual bool axisMoved(OIS::JoyStickEvent const &arg, int axis) override;

  public:
    Joystick(Joystick const &) = delete;
    Joystick(Joystick &&) = delete;
    virtual ~Joystick(void) = default;
    Joystick &operator=(Joystick const &) = delete;
    Joystick &operator=(Joystick &&) = delete;

    /// Register a state callback
    /// This callback takes in parameter a boolean, true if it's a current state,
    /// otherwise false.
    /// It should return false if the game should exit, true otherwise.
    void registerCallback(joystickState state, std::function<bool(bool)> const &);

    /// Clear all Button callback
    void clearCallbacks(void);

    /// Joystick singleton getter & instance
    struct JoystickState;
    static Joystick &getJoystick(void);

    /// Let you access each button indivually (unbuffered input)
    static JoystickState getStates(void);

    /// Equivalent to isKeyDown for JoyStick states.
    bool isStateUp(joystickState js);

    struct JoystickState
    {
        constexpr JoystickState(void) = default;
        ~JoystickState(void) = default;
        bool operator[](joystickState &&);
    };
};

#endif // !JOYSTICK_HPP_
