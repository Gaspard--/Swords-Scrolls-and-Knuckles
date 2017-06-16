#include "Spell.hpp"

Spell::Spell(std::function<void(Logic &, Player &)> cast,
	     unsigned int cooldown)
  : cast(cast)
  , cooldown(cooldown)
  , timeLeft(0u)
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
    {
      cast(logic, player);
      timeLeft = cooldown;
    }
  timeLeft -= !!timeLeft;
}
