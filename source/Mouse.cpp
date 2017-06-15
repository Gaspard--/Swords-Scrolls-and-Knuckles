#include "Mouse.hpp"

Mouse Mouse::mouseInstance;

Mouse &Mouse::getMouse(void) {
  return mouseInstance;
}

Mouse::Mouse(void)
  : Input<OIS::Mouse, OIS::MouseListener>()
{}

bool Mouse::mouseMoved(OIS::MouseEvent const &) {
  return true;
}

bool Mouse::mousePressed(OIS::MouseEvent const &event, OIS::MouseButtonID id) {
  try {
    keys.at(id)(event);
  }
  catch (std::out_of_range const &) {}
  return (true);
}

bool Mouse::mouseReleased(OIS::MouseEvent const &, OIS::MouseButtonID) {
  return true;
}

void Mouse::registerCallback(OIS::MouseButtonID id, std::function<void(OIS::MouseEvent const &)> const &fn)
{
  keys[id] = fn;
}

void Mouse::clearCallbacks(void) {
  keys.clear();
}
