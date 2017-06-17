#ifndef PROJECTILE_HPP
# define PROJECTILE_HPP

# include "Fixture.hpp"

class SaveState;
class Enemy;
class Logic;

class Projectile : public Fixture
{
private:
public:
  bool toRemove;

  Projectile() = default;

  constexpr Projectile(Vect<2u, double> pos, Vect<2u, double> speed)
  : Fixture{0.2, pos, speed}
    , toRemove(false)
  {
  }

  constexpr void update(Logic &logic)
  {
    pos += speed;
  }
  void   serialize(SaveState &state) const;
};

#endif
