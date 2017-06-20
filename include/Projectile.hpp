#ifndef PROJECTILE_HPP
# define PROJECTILE_HPP

# include <functional>
# include <unordered_map>

# include "Fixture.hpp"

class SaveState;
class Controllable;
class Logic;
class Projectile;

namespace ProjectileType
{
  static constexpr unsigned int const ARROW{0};
  static constexpr unsigned int const BOUNCY_ARROW{1};
  static constexpr unsigned int const ICE_PILLAR{2};
  static constexpr unsigned int const FIRE_BALL{3};
  static constexpr unsigned int const COOLDOWN_RESET{4};
  static constexpr unsigned int const HEAL{5};
  static constexpr unsigned int const GOLD{6};
  static constexpr unsigned int const GOLD5{7};
  static constexpr unsigned int const GOLD20{8};
  static constexpr unsigned int const GOLD50{9};
  static constexpr unsigned int const EXPLOSION{10};
  static constexpr unsigned int const HIT1{11};
  static constexpr unsigned int const HIT2{12};
};

class Projectile : public Fixture
{
public:
  unsigned int type;
  unsigned int timeLeft;

  Projectile() = default;

  constexpr Projectile(Vect<2u, double> pos, Vect<2u, double> speed,
		       unsigned int type, double size = 0.2, unsigned int removeIn = ~0u)
  : Fixture{size, pos, speed, true}
    , type(type)
    , timeLeft(removeIn)
  {
  }

  constexpr bool doTerrainCollision()
  {
    return type != ProjectileType::EXPLOSION
      && type != ProjectileType::HIT1
      && type != ProjectileType::HIT2;
  }

  constexpr bool doCollision() const
  {
    return true;
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

  constexpr bool doSpin()
  {
    return (type == ProjectileType::FIRE_BALL
	    || (type >= ProjectileType::GOLD && type <= ProjectileType::GOLD50)
	    || type == ProjectileType::HEAL
	    || type == ProjectileType::COOLDOWN_RESET);
  }

  void   serialize(SaveState &state) const;
  void   unserialize(LoadGame &);
};

class Enemy;

struct ProjectileReaction
{
  std::function<void(Controllable &, Projectile &)> hitEnemy;
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
