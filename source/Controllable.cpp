#include "Controllable.hpp"
#include "SaveGame.hpp"

void    Controllable::serialize(SaveState &state) const
{
  state.serialize(input);
  state.serialize(dir);
  state.serialize(targetDir);
  state.serialize(stun);
  state.serialize(locked);
  state.serialize(health);
  state.serialize(maxHealth);
}
