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
  unsigned int id;
  unsigned int ai;
  bool mounted;
  unsigned int gold;
  Vect<3u, Spell> spells;

public:
  template<class... PARAMS>
  Player(PlayerId id, Vect<3u, Spell> &&spells, PARAMS &&... params)
    : Controllable(std::forward<PARAMS>(params)...)
    , id(static_cast<int>(id))
    , ai(0)
    , mounted(false)
    , gold(0u)
    , spells(std::move(spells))
  {}

  Player() = default;
  Player(Player const &) = delete;
  Player(Player &&) = default;

  void checkSpells(Logic &);
  void resetCooldowns();
  void addGold(unsigned int);
  void setAttacking(unsigned int index, bool attacking);

  constexpr Vect<3u, Spell> const &getSpells() const
  {
    return (spells);
  }

  void setAI(unsigned int ai);
  unsigned int getAI(void) const;

  void setMounted(bool);
  bool isMounted(void) const;

  // In seconds / 10
  unsigned int getSpellTimeleft(size_t i) const;
  int getId(void) const;

  void serialize(SaveState &state) const;
  void unserialize(LoadGame &game);

  constexpr unsigned int getGold(void) const {
    return (gold);
  }

  static Player makeArcher(Vect<2u, double> pos);
  static Player makeMage(Vect<2u, double> pos);
  static Player makeTank(Vect<2u, double> pos);
  static Player makeWarrior(Vect<2u, double> pos);
  static Player makePlayer(Vect<2u, double> pos, PlayerId);
};

#endif // !PLAYER_HPP
