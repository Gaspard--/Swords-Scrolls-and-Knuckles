#include "Option.hpp"

Option::Option(std::string const &n, bool d, std::function<void(bool)> const &cb)
  : activated(d)
  , name(n)
  , callback(cb)
{}

bool Option::isActivated(void) const {
  return (activated);
}

void Option::setOption(bool b) {
  if (b != activated) {
    callback(b);
    activated = b;
  }
}

std::string const &Option::getName(void) const {
  return (name);
}
