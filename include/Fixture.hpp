#ifndef FIXTURE_HPP
# define FIXTURE_HPP

# include "Vect.hpp"

class SaveState;
struct Fixture
{
  double radius;
  Vect<2u, double> pos;
  Vect<2u, double> speed;

  constexpr double getRadius() const
  {
    return radius;
  }

  constexpr Vect<2u, double> getPos() const
  {
    return (pos);
  }

  constexpr Vect<2u, double> getSpeed() const
  {
    return (speed);
  }
  void  serialize(SaveState &state) const;
};

#endif
