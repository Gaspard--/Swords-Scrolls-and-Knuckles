#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "Controllable.hpp"
# include "Spell.hpp"

class Logic;

class Player : public Controllable
{
private:
  Vect<3u, Spell> spells;

public:
  template<class... PARAMS>
  Player(Vect<3u, Spell> &&spells, PARAMS &&... params)
    : Controllable(std::forward<PARAMS>(params)...)
    , spells(std::move(spells))
  {}

  Player() = default;
  Player(Player const &) = delete;
  Player(Player &&) = default;

  void checkSpells(Logic &);
  void setAttacking(unsigned int index, bool attacking);

  // In seconds / 10
  int getSpellTimeleft(size_t i) const;

  // ARCHER
  void shootArrow(Logic &);

  static Player makeArcher(Vect<2u, double> pos);
};

#endif // !PLAYER_HPP
