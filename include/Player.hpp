#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "Controllable.hpp"

class Logic;

class Player : public Controllable
{
private:

public:
  using Controllable::Controllable;
  using Controllable::update;
};

#endif
