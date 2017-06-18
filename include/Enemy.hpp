#ifndef ENEMY_HPP
# define ENEMY_HPP

# include "Controllable.hpp"

class Player;
class Logic;

class Enemy : public Controllable
{
private:

public:
  unsigned int ai;

public:
  Enemy() = default;
  template<class... PARAMS>
  Enemy(unsigned int ai, PARAMS &&... params)
    : Controllable(std::forward<PARAMS>(params)...)
    , ai(ai)
  {}

  void  serialize(SaveState &state) const;
  void  unserialize(LoadGame &);
};

#endif
