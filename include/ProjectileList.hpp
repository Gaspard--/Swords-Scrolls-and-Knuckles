#ifndef PROJECTILE_LIST_HPP
# define  PROJECTILE_LIST_HPP

#include <unordered_map>
#include "Projectile.hpp"

/**
 * bounciness: 0.0 follow wall, 1.0, bounce back at same speed.
 */
struct BounceResponse
{
  double bounciness;

  constexpr void operator()(Fixture &fixture, Vect<2u, double> dir)
  {
    fixture.speed -= dir * fixture.speed.scalar(dir) * (2.0);
    fixture.speed *= bounciness;
  }
};

class ProjectileList
{
private:
  std::unordered_map<unsigned int, ProjectileReaction> list;

public:
  static constexpr unsigned int const ARROW{0};
  static constexpr unsigned int const BOUNCY_ARROW{1};
  static constexpr unsigned int const ICE_PILLAR{2};

  ProjectileList();
  ProjectileReaction &operator[](unsigned int);
};

#endif
