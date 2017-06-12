#ifndef FIXTURE_HPP
# define FIXTURE_HPP

# include "Vect.hpp"

struct Fixture
{
  double radius;
  Vect<2u, double> pos;
  Vect<2u, double> speed;

  constexpr double getRadius() const
  {
    return radius;
  }

  constexpr Vect<2u, float> getPos() const
  {
    return (pos);
  }

  constexpr Vect<2u, float> getSpeed() const
  {
    return (speed);
  }
};

#endif
