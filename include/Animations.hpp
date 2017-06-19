#ifndef ANIMATIONS_HPP
# define ANIMATIONS_HPP

namespace Animations
{
  constexpr char const IDLE[] = "idle";

  namespace Controllable
  {
    constexpr char const WALK[] = "Walk";
    constexpr char const STAND[] = "Stand";
    constexpr char const STUN[] = "Stun";
    
    namespace Player
    {
      constexpr char const WALK_RIDE[] = "Walk_Ride";
      constexpr char const STAND_RIDE[] = "Stand_Ride";
      constexpr char const ATTACK[] = "Attack";
    }
    constexpr char const TAUNT[] = "Taun";

    // Archer-only animations will go here
    namespace Archer
    {
      constexpr char const JUMP[] = "Spell_A"; // JUMP
      constexpr char const SPELL_B[] = "Spell_B"; 
      constexpr char const SPELL_C[] = "Spell_C";
      constexpr char const SPELL_CHANNEL[] = "Spell_Channel";
      constexpr char const DASH[] = "Spell_D";
      constexpr char const SPELL_E[] = "Spell_E";
      constexpr char const SPELL_FORWARD[] = "Spell_Forward";
      constexpr char const SPELL_OMNI[] = "Spell_Omni";
    };

    namespace Warrior
    {
      constexpr char const SPELL_A[] = "Spell_A";
      constexpr char const SPELL_B[] = "Spell_B";
      constexpr char const JUMP[] = "Spell_C";
      constexpr char const SPELL_CHANNEL[] = "Spell_Channel";
      constexpr char const SPELL_D[] = "Spell_D";
      constexpr char const HAMMER_DOWN[] = "Spell_E";
      constexpr char const SPELL_FORWARD[] = "Spell_Forward";
      constexpr char const SPELL_OMNI[] = "Spell_Omni";
    };

    namespace Tank
    {
      constexpr char const SPELL_A[] = "Spell_A";
      constexpr char const SPELL_B[] = "Spell_B";
      constexpr char const SPELL_C[] = "Spell_C";
      constexpr char const SPELL_CHANNEL[] = "Spell_Channel";
      constexpr char const JUMP[] = "Spell_D";
      constexpr char const SPELL_E[] = "Spell_E";
      constexpr char const SPELL_FORWARD[] = "Spell_Forward";
      constexpr char const SPELL_OMNI[] = "Spell_Omni";
    };

    namespace Mage
    {
      constexpr char const SPELL_A[] = "Spell_A";
      constexpr char const SPELL_B[] = "Spell_B";
      constexpr char const SPELL_C[] = "Spell_C";
      constexpr char const SPELL_CHANNEL[] = "Spell_Channel";
      constexpr char const SPELL_D[] = "Spell_D";
      constexpr char const SPELL_E[] = "Spell_E";
      constexpr char const SPELL_FORWARD[] = "Spell_Forward";
      constexpr char const SPELL_OMNI[] = "Spell_Omni";
    };

    namespace Enemy
    {
      constexpr char const DEATH[] = "Death";

      constexpr char const ATTACK_01[] = "Attack";
      constexpr char const ATTACK_02[] = "Attack_01";
    };
  }

  namespace Mount
  {
    constexpr char const WALK[] = "Walk";
    constexpr char const STAND[] = "Stand";
  };

};

#endif // !ANIMATIONS_HPP
