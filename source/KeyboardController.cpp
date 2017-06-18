#include "KeyboardController.hpp"

KeyboardController::KeyboardController(std::map<unsigned int, OIS::KeyCode> &&km)
: keymap(std::move(km))
{
}
