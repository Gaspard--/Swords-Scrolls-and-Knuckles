#ifndef CONTROLLABLE_HPP
# define CONTROLLABLE_HPP

# include "Fixture.hpp"

class Logic;

class Controllable : public Fixture
{
private:
  Vect<2u, double> input;
  unsigned int stun;

public:
  template<class... PARAMS>
  constexpr Controllable(PARAMS &&... params)
  : Fixture{std::forward<PARAMS>(params)..., Vect<2u, double>{0, 0}}
    , input(0.0, 0.0)
    , stun(0)
  {
  }
  
  constexpr void update(Logic &)
  {
    if (!stun)
      speed = input;
    else
      --stun;
    pos += speed;
  }

  constexpr void knockBack(Vect<2u, double> speed, unsigned int stun)
  {
    this->speed = speed;
    this->stun = stun;
  }

  constexpr bool isWalking()
  {
    return !stun && !input.equals({0.0, 0.0});
  }
};

#endif
