#ifndef KEYBOARD_HPP
# define KEYBOARD_HPP

# include <functional>
# include <OISKeyboard.h>
# include "Input.hpp"

class Keyboard : public Input<OIS::Keyboard>
{
    std::map<OIS::KeyCode, std::function<bool(bool)>> keys;

    /// Singleton instance
    static Keyboard keyboardInstance;

    Keyboard(void);
  protected:
    /// OIS::KeyListener
    virtual bool keyPressed(OIS::KeyEvent const &ke);
    virtual bool keyReleased(OIS::KeyEvent const &ke);

  public:
    Keyboard(Keyboard const &) = delete;
    Keyboard(Keyboard &&) = delete;
    virtual ~Keyboard(void) = default;
    Keyboard &operator=(Keyboard const &) = delete;
    Keyboard &operator=(Keyboard &&) = delete;

    /// Register a key callback
    /// This callback takes in parameter a boolean, true if the key is pressed,
    /// false if it's released.
    /// It should return false if the game should exit, true otherwise.
    void registerCallback(OIS::KeyCode, std::function<bool(bool)> const &);

    /// Clear all key callback
    void clearCallbacks(void);

    /// Keyboard singleton getter & instance
    struct KeyboardKey;
    static Keyboard &getKeyboard(void);

    /// Let you access each keys indivually (unbuffered input)
    static KeyboardKey getKeys(void);

    struct KeyboardKey
    {
	KeyboardKey(void) = default;
	~KeyboardKey(void) = default;
	bool operator[](OIS::KeyCode &&);
    };
};

#endif // !KEYBOARD_HPP
