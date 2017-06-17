#ifndef PROJECTILE_HPP
# define PROJECTILE_HPP

# include <functional>
# include <unordered_map>

# include "Fixture.hpp"

class Logic;
class Projectile;

namespace ProjectileType
{
  static constexpr unsigned int const ARROW{0};
  static constexpr unsigned int const BOUNCY_ARROW{1};
  static constexpr unsigned int const ICE_PILLAR{2};
  static constexpr unsigned int const FIRE_BALL{3};
};

class Projectile : public Fixture
{
public:
  unsigned int type;
  unsigned int timeLeft;

  Projectile() = default;

  constexpr Projectile(Vect<2u, double> pos, Vect<2u, double> speed,
		       unsigned int type, double size = 0.2, unsigned int removeIn = ~0u)
  : Fixture{size, pos, speed}
    , type(type)
    , timeLeft(removeIn)
  {
  }

  constexpr void remove()
  {
    timeLeft = 0;
  }

  constexpr bool shouldBeRemoved() const
  {
    return !timeLeft;
  }
  
  constexpr void update(Logic &)
  {
    timeLeft -= !!timeLeft;
    pos += speed;
  }
};

class Enemy;

struct ProjectileReaction
{
  std::function<void(Enemy &, Projectile &)> hitEnemy;
  std::function<void(Projectile &, Vect<2u, double>)> wallResponse;
};

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
  std::unordered_map<unsigned int, ProjectileReaction> map;

public:
  ProjectileList();
  ProjectileReaction const &operator[](unsigned int) const;
};

#endif
