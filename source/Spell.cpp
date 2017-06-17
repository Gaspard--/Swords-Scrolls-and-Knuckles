#include "Spell.hpp"
#include "Logic.hpp"

void Spell::update(Logic &logic, Player &player)
{
  if (!timeLeft && active)
    timeLeft = cooldown;
  if ((cooldown - timeLeft) < duration)
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
    player.invulnerable = time != 29;
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
      logic.spawnProjectile(player.getPos(), {0.0, 0.0}, ProjectileType::ICE_PILLAR);
    player.invulnerable = time != 480;
  };
}

std::function<void(Logic &, Player &, unsigned int)> const &SpellList::operator[](unsigned int type) const
{
  return map.at(type);
}
