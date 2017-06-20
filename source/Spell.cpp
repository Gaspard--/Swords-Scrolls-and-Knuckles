#include "Spell.hpp"
#include "Logic.hpp"

void Spell::update(Logic &logic, Player &player)
{
  if (!timeLeft && active)
    timeLeft = cooldown;
  if (hasEffect())
    logic.spellList[type](logic, player, cooldown - timeLeft);
  timeLeft -= !!timeLeft;
}

SpellList::SpellList()
{
  map[SpellType::ARROW_SHOT] = [](Logic &logic, Player &player, unsigned int time) {
    if (time == 9)
      logic.spawnProjectile(player.getPos(), player.getDir().normalized() * 0.12, ProjectileType::ARROW);
  };
  map[SpellType::JUMP] = [](Logic &, Player &player, unsigned int time) {
    if (!time)
      player.dash(3.0, 30);
  };
  map[SpellType::ARROW_ULTI] = [](Logic &logic, Player &player, unsigned int time) {
    if (!(time % 20))
      logic.spawnProjectile(player.getPos(), player.getDir().normalized() * 0.15, ProjectileType::BOUNCY_ARROW);
  };

  map[SpellType::FIRE_BALL] = [](Logic &logic, Player &player, unsigned int time) {
    if (time == 9)
      logic.spawnProjectile(player.getPos(), player.getDir().normalized() * 0.08, ProjectileType::FIRE_BALL);
  };

  map[SpellType::FROST_WALL] = [](Logic &logic, Player &player, unsigned int time) {
    if (!(time % 20))
      {
	logic.spawnProjectile(player.getPos(), {0.0, 0.0}, ProjectileType::ICE_PILLAR, 0.2, 240);
	player.invulnerable = 20;
      }
    player.setMounted(time != 480);
  };
  map[SpellType::DASH] = [](Logic &logic, Player &player, unsigned int time) {
    if (!time)
      player.dash(3.0, 30);
    if (time == 25)
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
  
}

std::function<void(Logic &, Player &, unsigned int)> const &SpellList::operator[](unsigned int type) const
{
  return map.at(type);
}
