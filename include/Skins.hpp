#ifndef SKINS_HPP
# define SKINS_HPP

namespace Skins
{
  using Skin = char const *;
  namespace Archer
  {
    constexpr Skin BASE = "sylvanas.mesh";
    constexpr Skin HIGH_ELF = "sylvanas_highelf.mesh";
  };
  namespace Tank
  {
    constexpr Skin BASE = "muradin.mesh";
    constexpr Skin MAGNI = "muradin_magni.mesh";
  };
  namespace Mage
  {
    constexpr Skin BASE = "jaina.mesh";
    constexpr Skin CLAUS = "jaina_claus.mesh";
  };
  namespace Warrior
  {
    constexpr Skin BASE = "thrall.mesh";
    constexpr Skin RED = "thrall_red.mesh";
  };
};

#endif // !SKINS_HPP
