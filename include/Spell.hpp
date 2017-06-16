#ifndef SPELL_HPP
# define SPELL_HPP

# include <functional>

class Logic;
class Player;

struct Spell
{
  std::function<void(Logic &, Player &)> cast;
  unsigned int cooldown;
  unsigned int timeLeft;
  bool active;

  Spell();
  Spell(std::function<void(Logic &, Player &)> cast, unsigned int cooldown);
  Spell(Spell const &) = delete;
  Spell(Spell &&) = default;

  void update(Logic &, Player &);
};

#endif
