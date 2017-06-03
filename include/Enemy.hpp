#ifndef ENEMY_HPP
# define ENEMY_HPP

# include "Fixture.hpp"

class Player;
class Logic;

class Enemy : public Fixture
{
private:
public:
  void hit(Player &player);
  void update(Logic &logic);
};

#endif
