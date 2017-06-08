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
  : Fixture{0.2, pos, speed}
  {
  }
  
  constexpr void hit(Enemy &)
  {
  }

  constexpr void update(Logic &logic)
  {
    pos += speed;
  }
};

#endif
