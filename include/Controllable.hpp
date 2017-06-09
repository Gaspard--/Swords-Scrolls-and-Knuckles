#ifndef CONTROLLABLE_HPP
# define CONTROLLABLE_HPP

# include "Fixture.hpp"

class Logic;

class Controllable : public Fixture
{
private:
  Vect<2u, double> input;
  Vect<2u, double> dir;
  unsigned int stun;

public:
  template<class... PARAMS>
  constexpr Controllable(PARAMS &&... params)
  : Fixture{std::forward<PARAMS>(params)..., Vect<2u, double>{0, 0}}
    , input(0.0, 0.0)
    , stun(0)
  {
  }
  
  constexpr void update(Logic &logic);

  constexpr void knockBack(Vect<2u, double> speed, unsigned int stun)
  {
    this->speed = speed;
    this->stun = stun;
  }

  constexpr bool isWalking() const
  {
    return !stun && !input.equals({0.0, 0.0});
  }

  // setter only.
  constexpr void setInput(Vect<2u, double> input)
  {
    this->input = input;
  }

  constexpr Vect<2u, double> getDir() const
  {
    return dir;
  }
};

# include "Logic.hpp"

constexpr void Controllable::update(Logic &logic)
{
  if (!stun)
    {
      speed = input;
      dir = input;
    }
  else
    --stun;
  pos += speed;
}


#endif
