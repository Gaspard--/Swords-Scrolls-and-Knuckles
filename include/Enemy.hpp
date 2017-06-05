#ifndef ENEMY_HPP
# define ENEMY_HPP

# include "Controllable.hpp"

class Player;
class Logic;

class Enemy : public Controllable
{
private:

public:
  using Controllable::Controllable;
  void hit(Player &player);
  void update(Logic &logic);
};

#endif
