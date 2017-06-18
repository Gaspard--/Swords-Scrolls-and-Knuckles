#include "Controllable.hpp"
#include "SaveGame.hpp"
#include "LoadGame.hpp"

void    Controllable::serialize(SaveState &state) const
{
  state.serialize(input);
  state.serialize(dir);
  state.serialize(targetDir);
  state.serialize(stun);
  state.serialize(locked);
  state.serialize(health);
  state.serialize(maxHealth);
  state.serialize(dePopCounter);
}

void   Controllable::unserialize(LoadGame &game)
{
  game.unserialize(input);
  game.unserialize(dir);
  game.unserialize(targetDir);
  game.unserialize(stun);
  game.unserialize(locked);
  game.unserialize(health);
  game.unserialize(maxHealth);
  game.unserialize(dePopCounter);
}
