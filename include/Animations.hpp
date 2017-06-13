#ifndef ANIMATIONS_HPP
# define ANIMATIONS_HPP

namespace Animations
{
  constexpr char const IDLE[] = "idle";

  namespace Controllable
  {
    constexpr char const WALK[] = "Walk";
    constexpr char const WALK_RIDE[] = "Walk_Ride";
    constexpr char const STAND[] = "Stand";
    constexpr char const STAND_RIDE[] = "Stand_Ride";
    constexpr char const ATTACK[] = "Attack";
    constexpr char const STUN[] = "Stun";
    constexpr char const TAUNT[] = "Taun";

    // Archer-only animations will go here
    namespace Archer
    {
      constexpr char const SPELL_A[] = "Spell_A";
    }

  }
  namespace Ennemy
  {
    constexpr char const STAND[] = "Stand";
    constexpr char const STUN[] = "Stun";
    constexpr char const WALK[] = "Walk";
    constexpr char const DEATH[] = "Death";

    constexpr char const ATTACK_01[] = "Attack";
    constexpr char const ATTACK_02[] = "Attack_01";
  };
};

#endif // !ANIMATIONS_HPP
