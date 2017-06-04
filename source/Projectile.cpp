#include "Projectile.hpp"
#include "Enemy.hpp"
#include "Logic.hpp"

void Projectile::hit(Enemy &)
{
}

void Projectile::update(Logic &logic)
{
  pos += speed;
}
