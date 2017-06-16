#ifndef CONTROLLABLE_HPP
# define CONTROLLABLE_HPP

# include "Fixture.hpp"

class Logic;

class Controllable : public Fixture
{
private:
  Vect<2u, double> input;
  Vect<2u, double> dir;
  Vect<2u, double> targetDir;
  unsigned int stun;
  bool locked;
  unsigned int health;
  unsigned int maxHealth;

public:
  template<class... PARAMS>
  constexpr Controllable(unsigned int health, PARAMS &&... params)
  : Fixture{std::forward<PARAMS>(params)..., Vect<2u, double>{0.0, 0.0}}
    , input{0.0, 0.0}
    , dir{0.0, 1.0}
    , targetDir(dir)
    , stun(0)
    , locked(false)
    , health(health)
    , maxHealth(health)
  {
  }

  constexpr void update(Logic &logic);

  constexpr void knockback(Vect<2u, double> speed, unsigned int stun)
  {
    targetDir = -speed.normalized();
    this->speed = speed;
    this->stun = stun;
  }

  constexpr bool isWalking() const
  {
    return !stun && !input.equals({0.0, 0.0});
  }

  constexpr bool isStun() const
  {
    return stun;
  }

  // setter only.
  constexpr void setInput(Vect<2u, double> input)
  {
    if (!stun && input.length2() > 0)
      targetDir = input.normalized();
    this->input = input;
  }

  // setter only.
  constexpr void setLocked(bool locked)
  {
    this->locked = locked;
  }

  constexpr void setInputPy(double a, double b)
  {
    this->input[0] = a;
    this->input[1] = b;
  }

  constexpr Vect<2u, double> getDir() const
  {
    return dir;
  }
};

#endif // !CONTROLLABLE_HPP
