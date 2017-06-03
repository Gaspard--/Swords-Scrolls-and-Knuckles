#ifndef PROJECTILE_HPP
# define PROJECTILE_HPP

# include "Fixture.hpp"

class Enemy;
class Logic;

class Projectile : public Fixture
{
private:
public:
  Projectile() = default;

  constexpr Projectile(Vect<2u, double> pos, Vect<2u, double> speed)
  : Fixture{1.0, pos, speed}
  {
  }
  void hit(Enemy &e);
  void update(Logic &logic);
};

#endif
