#ifndef KEYBOARDCONTROLLER_HPP_
# define KEYBOARDCONTROLLER_HPP_

# include <OISKeyboard.h>

namespace KBACTION
{
    constexpr unsigned int GO_UP = 1u;
    constexpr unsigned int GO_DOWN = 2u;
    constexpr unsigned int GO_LEFT = 3u;
    constexpr unsigned int GO_RIGHT = 4u;
    constexpr unsigned int SPELL1 = 5u;
    constexpr unsigned int SPELL2 = 6u;
    constexpr unsigned int SPELL3 = 7u;
    constexpr unsigned int LOCK = 8u;
}

class KeyboardController
{
public:
  KeyboardController(std::map<unsigned int, OIS::KeyCode> &&);
  ~KeyboardController() = default;

  std::map<unsigned int, OIS::KeyCode> keymap;
};

#endif // !KEYBOARDCONTROLLER_HPP_
