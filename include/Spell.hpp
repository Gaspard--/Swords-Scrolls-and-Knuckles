#ifndef SPELL_HPP
# define SPELL_HPP

# include <functional>
# include <unordered_map>

class Logic;
class Player;

namespace SpellType
{
  constexpr unsigned int ARROW_SHOT{0u};
  constexpr unsigned int JUMP{1u};
  constexpr unsigned int GROW{2u};

  constexpr unsigned int FIRE_ULTI{3u};
  constexpr unsigned int FIRE_BALL{4u};
  constexpr unsigned int FROST_WALL{5u};

  constexpr unsigned int DASH{6u};
  constexpr unsigned int HIT1{7u};
  constexpr unsigned int HIT2{8u};
  constexpr unsigned int SPIN{9u};
  constexpr unsigned int CHOOCHOO{10u};

};

struct Spell
{
  unsigned int type;
  unsigned int cooldown;
  unsigned int duration;
  unsigned int timeLeft;
  bool active;
  bool reset;

  Spell() = default;

  constexpr Spell(unsigned int type, unsigned int cooldown,
		  unsigned int duration = 1, unsigned int timeLeft = 0)
  : type(type)
    , cooldown(cooldown)
    , duration(duration)
    , timeLeft(timeLeft)
    , active(false)
    , reset(false)
  {}

  void update(Logic &, Player &);

  constexpr unsigned int startedSince() const
  {
    return (cooldown - timeLeft);
  }

  constexpr bool hasEffect() const
  {
    return (startedSince() < duration);
  }
};

class SpellList
{
private:
  std::unordered_map<unsigned int, std::function<void(Logic &, Player &, unsigned int)>> map;

public:
  SpellList();

  std::function<void(Logic &, Player &, unsigned int)> const &operator[](unsigned int type) const;
};

#endif
