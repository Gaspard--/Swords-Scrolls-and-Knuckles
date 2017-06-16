#include "Mouse.hpp"

Mouse Mouse::mouseInstance;

Mouse &Mouse::getMouse(void) {
  return mouseInstance;
}

Mouse::Mouse(void)
  : Input<OIS::Mouse, OIS::MouseListener>()
{}

bool Mouse::mouseMoved(OIS::MouseEvent const &event) {
  for (auto const &it : moveCallbacks) {
    it(
      static_cast<Ogre::Real>(event.state.X.abs),
      static_cast<Ogre::Real>(event.state.Y.abs)
    );
  }
  return true;
}

bool Mouse::mousePressed(OIS::MouseEvent const &event, OIS::MouseButtonID id) {
  try {
    keysCallbacks.at(id)(event);
  }
  catch (std::out_of_range const &) {}
  return (true);
}

bool Mouse::mouseReleased(OIS::MouseEvent const &, OIS::MouseButtonID) {
  return true;
}

void Mouse::registerCallback(OIS::MouseButtonID id, std::function<void(OIS::MouseEvent const &)> const &fn)
{
  keysCallbacks[id] = fn;
}

void Mouse::registerMouseMoveCallback(std::function<void(Ogre::Real, Ogre::Real)> const &fn) {
  moveCallbacks.emplace_back(fn);
}

void Mouse::clearCallbacks(void) {
  keysCallbacks.clear();
  moveCallbacks.clear();
}
