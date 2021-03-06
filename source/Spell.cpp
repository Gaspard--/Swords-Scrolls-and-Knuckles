#include "Spell.hpp"
#include "Logic.hpp"

void Spell::update(Logic &logic, Player &player)
{
  if (!timeLeft && active)
    timeLeft = cooldown;
  if (hasEffect())
    logic.spellList[type](logic, player, cooldown - timeLeft);
  else if (reset)
    {
      reset = false;
      timeLeft = 0;
    }
  timeLeft -= !!timeLeft;
}

SpellList::SpellList()
{
  map[SpellType::ARROW_SHOT] = [](Logic &logic, Player &player, unsigned int time) {
    if (time == 90)
      {
	unsigned int count(player.radius * 6 - 2.0);

	for (unsigned int i(0); i < count; ++i)
	  {
	    Vect<2u, double> const dir(player.getDir().normalized() * 0.12);
	    Vect<2u, double> const side{dir[1], -dir[0]};

	    logic.spawnProjectile(player.getPos(), dir + (side * (i - (count - 1) * 0.5)) * 0.3, ProjectileType::BOUNCY_ARROW, 0.2, 360);
	  }
      }
  };
  map[SpellType::JUMP] = [](Logic &, Player &player, unsigned int time) {
    if (!time)
      player.dash(6.0 * player.radius, 30);
  };
  map[SpellType::FIRE_ULTI] = [](Logic &logic, Player &player, unsigned int time) {
    if (time >= 40 && !(time % 10))
      logic.spawnProjectile(player.getPos() + player.getDir().normalized() * (time - 30) / 10.0, {0.0, 0.0}, ProjectileType::EXPLOSION, 1.0, 2);
  };

  map[SpellType::FIRE_BALL] = [](Logic &logic, Player &player, unsigned int time) {
    if (time == 40)
      logic.spawnProjectile(player.getPos(), player.getDir().normalized() * 0.08, ProjectileType::FIRE_BALL);
  };

  map[SpellType::FROST_WALL] = [](Logic &logic, Player &player, unsigned int time) {
    if (!(time % 20))
      {
	logic.spawnProjectile(player.getPos(), {0.0, 0.0}, ProjectileType::ICE_PILLAR, 0.2, 240);
	player.invulnerable = 20;
      }
  };
  map[SpellType::DASH] = [](Logic &logic, Player &player, unsigned int time) {
    if (!time)
      player.dash(3.0, 30);
    if (time == 35)
      logic.spawnProjectile(player.getPos(), {0.0, 0.0}, ProjectileType::EXPLOSION, 2.0, 2);
  };
  map[SpellType::HIT1] = [](Logic &logic, Player &player, unsigned int time) {
    if (time == 50)
      {
	logic.spawnProjectile(player.getPos() + player.getDir().normalized() * 0.5, player.getDir().normalized() * 0.2, ProjectileType::HIT1, 1.5, 2);
      }
  };
  map[SpellType::HIT2] = [](Logic &logic, Player &player, unsigned int time) {
    if (time == 180)
      {
	logic.spawnProjectile(player.getPos() + player.getDir().normalized() * 0.5, player.getDir().normalized() * 0.4, ProjectileType::HIT2, 1.5, 2);
      }
  };
  map[SpellType::GROW] = [](Logic &logic, Player &player, unsigned int time) {
    player.invulnerable = 1;
    if (time < 60)
      {
	player.radius = 0.5 * (1.0 + time / 60.0);
      }
    else if (time > 420)
      {
	player.radius = 0.5 * (1.0 + (480.0 - time) / 60.0);
      }
    else
      player.radius = 1.0;
    if (time == 239)
      player.radius = 0.5;
    if (!(time % 10))
      logic.spawnProjectile(player.getPos(), {0.0, 0.0}, ProjectileType::EXPLOSION, player.radius, 2);
  };
  map[SpellType::SPIN] = [](Logic &logic, Player &player, unsigned int time) {
    player.invulnerable = 1;
        if (time < 60)
      {
	player.radius = 0.5 * (1.0 + time / 60.0);
      }
    else if (time > 420)
      {
	player.radius = 0.5 * (1.0 + (480.0 - time) / 60.0);
      }
    else
      player.radius = 1.0;
    if (time == 239)
      player.radius = 0.5;
    if (!(time % 20))
      logic.spawnProjectile(player.getPos(), {0.0, 0.0}, ProjectileType::EXPLOSION, player.radius * 1.2, 2);
  };
  map[SpellType::CHOOCHOO] = [](Logic &logic, Player &player, unsigned int time) {
    player.invulnerable = 1;
    if (time % 50)
      logic.spawnProjectile(player.getPos() + player.getDir().normalized() * 0.5, player.getDir().normalized() * 0.2, ProjectileType::HIT1, 1.5, 2);
    player.speed += player.getDir().normalized() * 0.005;
  };
  
}

std::function<void(Logic &, Player &, unsigned int)> const &SpellList::operator[](unsigned int type) const
{
  return map.at(type);
}
