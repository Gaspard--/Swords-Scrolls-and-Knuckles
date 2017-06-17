#include "ProjectileList.hpp"
#include "Enemy.hpp"

ProjectileList::ProjectileList()
{
  list[(unsigned int)ARROW] =
    ProjectileReaction{
    [](Enemy &enemy, Projectile &projectile){
      enemy.knockback(projectile.speed.normalized() * 0.2, 10);
      projectile.toRemove = true;
    },
    [](Projectile &p, Vect<2u, double>){
      p.toRemove = true;
    }};
  list[(unsigned int)BOUNCY_ARROW] =
    ProjectileReaction{
    [](Enemy &enemy, Projectile &projectile){
      enemy.knockback(projectile.speed.normalized() * 0.2, 10);
      BounceResponse{1.0}(projectile, (enemy.pos - projectile.pos).normalized());
      projectile.type = ARROW;
      //      projectile.toRemove = true;
    },
    [](Projectile &p, Vect<2u, double> v){
      BounceResponse{1.0}(p, v);
      p.type = ARROW;
    }};
  list[(unsigned int)ICE_PILLAR] = 
    ProjectileReaction{
    [](Enemy &enemy, Projectile &projectile){
      enemy.knockback((enemy.pos - projectile.pos).normalized() * 0.03, 5);
      // projectile.toRemove = true;
    },
    [](Projectile &, Vect<2u, double>){
      // p.toRemove = true;
    }};
}

ProjectileReaction &ProjectileList::operator[](unsigned int n)
{
  return list.at(n);
}
