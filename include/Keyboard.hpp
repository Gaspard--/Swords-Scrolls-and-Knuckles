#ifndef KEYBOARD_HPP
# define KEYBOARD_HPP

# include <OISKeyboard.h>
# include "Input.hpp"

class Keyboard : public Input<OIS::Keyboard>
{
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

    /// Singleton getter
    struct KeyboardKey;
    static Keyboard &getKeyboard(void);
    static KeyboardKey getKeys(void);

    struct KeyboardKey
    {
	KeyboardKey(void) = default;
	~KeyboardKey(void) = default;
	bool operator[](OIS::KeyCode &&);
    };
};

#endif // !KEYBOARD_HPP
