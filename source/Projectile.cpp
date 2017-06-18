#include "Projectile.hpp"
#include "SaveGame.hpp"
#include "LoadGame.hpp"

void    Projectile::serialize(SaveState &state) const
{}

ProjectileList::ProjectileList()
{
  map[(unsigned int)ProjectileType::ARROW] =
    ProjectileReaction{
    [](Enemy &enemy, Projectile &projectile){
      enemy.knockback(projectile.speed.normalized() * 0.2, 10);
      projectile.remove();
    },
    [](Projectile &p, Vect<2u, double>){
      p.remove();
    }};
  map[(unsigned int)ProjectileType::BOUNCY_ARROW] =
    ProjectileReaction{
    [](Enemy &enemy, Projectile &projectile){
      enemy.knockback(projectile.speed.normalized() * 0.2, 10);
      BounceResponse{0.8}(projectile, (enemy.pos - projectile.pos).normalized());
      projectile.type = ProjectileType::ARROW;
    },
    [](Projectile &projectile, Vect<2u, double> v){
      BounceResponse{0.8}(projectile, v);
      projectile.type = ProjectileType::ARROW;
    }};
  map[(unsigned int)ProjectileType::ICE_PILLAR] =
    ProjectileReaction{
    [](Enemy &enemy, Projectile &projectile){
      enemy.knockback((enemy.pos - projectile.pos).normalized() * 0.03, 5);
    },
    [](Projectile &, Vect<2u, double>){
    }};
  map[(unsigned int)ProjectileType::FIRE_BALL] = // TODO
    ProjectileReaction{
    [](Enemy &enemy, Projectile &projectile){
      enemy.knockback((enemy.pos - projectile.pos).normalized() * 0.03, 5);
    },
    [](Projectile &, Vect<2u, double>){
    }};
}

ProjectileReaction const &ProjectileList::operator[](unsigned int n) const
{
  return map.at(n);
}

void    Projectile::unserialize(LoadGame &game)
{
  game.unserialize(type);
  game.unserialize(timeLeft);
}
