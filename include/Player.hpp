#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "Controllable.hpp"
# include "Spell.hpp"

class Logic;

enum class PlayerId
  {
    ARCHER = 0,
    MAGE = 1,
    TANK = 2,
    WARRIOR = 3
  };

class Player : public Controllable
{
private:
  unsigned int    id;
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

  static Player makeArcher(Vect<2u, double> pos);
  static Player makeMage(Vect<2u, double> pos);
  static Player makeTank(Vect<2u, double> pos);
  static Player makeWarrior(Vect<2u, double> pos);

  void  serialize(SaveState &state) const;
  void  unserialize(LoadGame &);
};

#endif // !PLAYER_HPP
