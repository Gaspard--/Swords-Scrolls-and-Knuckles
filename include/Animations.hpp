#ifndef ANIMATIONS_HPP
# define ANIMATIONS_HPP

namespace Animations
{
  constexpr char const IDLE[] = "idle";

  namespace Controllable
  {
    constexpr char const WALK[] = "Walk";
    constexpr char const STAND[] = "Stand";
    constexpr char const ATTACK[] = "Attack";
    constexpr char const STUN[] = "Stun";
    constexpr char const TAUNT[] = "Taun";

    // Archer-only animations will go here
    namespace Archer
    {
      constexpr char const SPELL_A[] = "Spell_A";
    }
  }

};

#endif // !ANIMATIONS_HPP
