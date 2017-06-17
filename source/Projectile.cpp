#include "Projectile.hpp"

Projectile::Projectile(Vect<2u, double> pos, Vect<2u, double> speed,
		       unsigned int type)
  : Fixture{0.2, pos, speed}
  , type(type)
  , toRemove(false)
{
}

void Projectile::update(Logic &)
{
  pos += speed;
}
