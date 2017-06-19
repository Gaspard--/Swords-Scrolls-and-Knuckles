#include "Projectile.hpp"
#include "SaveGame.hpp"
#include "LoadGame.hpp"

void    Projectile::serialize(SaveState &state) const
{}

ProjectileList::ProjectileList()
{
  map[(unsigned int)ProjectileType::ARROW] =
    ProjectileReaction{
    [](Controllable &controllable, Projectile &projectile){
      controllable.knockback(projectile.speed.normalized() * 0.2, 10);
      controllable.takeDamage(35);
      projectile.remove();
    },
    [](Projectile &p, Vect<2u, double>){
      p.remove();
    }};
  map[(unsigned int)ProjectileType::BOUNCY_ARROW] =
    ProjectileReaction{
    [](Controllable &controllable, Projectile &projectile){
      controllable.knockback(projectile.speed.normalized() * 0.2, 10);
      controllable.takeDamage(35);
      BounceResponse{0.8}(projectile, (controllable.pos - projectile.pos).normalized());
      projectile.type = ProjectileType::ARROW;
    },
    [](Projectile &projectile, Vect<2u, double> v){
      BounceResponse{0.8}(projectile, v);
      projectile.type = ProjectileType::ARROW;
    }};
  map[(unsigned int)ProjectileType::ICE_PILLAR] =
    ProjectileReaction{
    [](Controllable &controllable, Projectile &projectile){
      controllable.knockback((controllable.pos - projectile.pos).normalized() * 0.3, 5);
      controllable.takeDamage(5);
    },
    [](Projectile &, Vect<2u, double>){
    }};
  map[(unsigned int)ProjectileType::FIRE_BALL] = // TODO
    ProjectileReaction{
    [](Controllable &controllable, Projectile &projectile){
      projectile.timeLeft = 2;
      projectile.type = ProjectileType::EXPLOSION;
      projectile.radius = 2.0;
    },
    [](Projectile &projectile, Vect<2u, double>){
      projectile.timeLeft = 2;
      projectile.type = ProjectileType::EXPLOSION;
      projectile.radius = 2.0;
    }};
  map[(unsigned int)ProjectileType::EXPLOSION] = // TODO
    ProjectileReaction{
    [](Controllable &controllable, Projectile &projectile){
      controllable.knockback((controllable.pos - projectile.pos).normalized() * 0.2, 5);
      controllable.takeDamage(40);
    },
    [](Projectile &, Vect<2u, double>){
    }};
  map[(unsigned int)ProjectileType::COOLDOWN_RESET] =
    ProjectileReaction{
    [](Controllable &controllable, Projectile &projectile){
      projectile.remove();
    },
    [](Projectile &, Vect<2u, double>){
    }};
  map[(unsigned int)ProjectileType::HEAL] =
    ProjectileReaction{
    [](Controllable &controllable, Projectile &projectile){
      controllable.heal(100);
      projectile.remove();
    },
    [](Projectile &, Vect<2u, double>){
    }};
  map[(unsigned int)ProjectileType::GOLD] =
    ProjectileReaction{
    [](Controllable &controllable, Projectile &projectile){
      projectile.remove();
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
