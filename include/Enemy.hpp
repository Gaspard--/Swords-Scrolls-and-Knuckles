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
  template<class... PARAMS>
  Enemy(unsigned int ai, PARAMS &&... params)
    : Controllable(std::forward<PARAMS>(params)...)
    , ai(ai)
  {}
};

#endif
