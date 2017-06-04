#ifndef PLAYER_HPP
# define PLAYER_HPP

#include "Fixture.hpp"

class Logic;

class Player : public Fixture
{
private:
public:
  void update(Logic &);
};

#endif
