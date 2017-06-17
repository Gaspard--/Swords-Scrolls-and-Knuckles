#include "Spell.hpp"

Spell::Spell(std::function<void(Logic &, Player &, unsigned int)> cast,
	     unsigned int cooldown, unsigned int duration, unsigned int timeLeft)
  : cast(cast)
  , cooldown(cooldown)
  , duration(duration)
  , timeLeft(timeLeft)
  , active(false)
{
}

Spell::Spell()
  : Spell(nullptr, 0u)
{
}

void Spell::update(Logic &logic, Player &player)
{
  if (!timeLeft && active)
    timeLeft = cooldown;
  if ((cooldown - timeLeft) < duration)
    cast(logic, player, cooldown - timeLeft);
  timeLeft -= !!timeLeft;
}
