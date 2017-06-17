#ifndef SPELL_HPP
# define SPELL_HPP

# include <functional>

class Logic;
class Player;

struct Spell
{
  std::function<void(Logic &, Player &, unsigned int)> cast;
  unsigned int cooldown;
  unsigned int duration;
  unsigned int timeLeft;
  bool active;

  Spell();
  Spell(std::function<void(Logic &, Player &, unsigned int)> cast, unsigned int cooldown,
	unsigned int duration = 1, unsigned int timeLeft = 0);
  Spell(Spell const &) = delete;
  Spell(Spell &&) = default;

  void update(Logic &, Player &);
};

#endif
