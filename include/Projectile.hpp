#ifndef PROJECTILE_HPP
# define PROJECTILE_HPP

# include <functional>

# include "Fixture.hpp"
# include "Projectile.hpp"

class SaveState;
class Enemy;
class Logic;
class Projectile;

struct ProjectileReaction
{
  std::function<void(Enemy &, Projectile &)> hitEnemy;
  std::function<void(Projectile &, Vect<2u, double>)> wallResponse;
};



class Projectile : public Fixture
{
private:;

public:
unsigned int type;
  bool toRemove;

  Projectile() = default;

  Projectile(Vect<2u, double> pos, Vect<2u, double> speed,
	     unsigned int type);

  void   serialize(SaveState &state) const;
  void   update(Logic &);
};

#endif
