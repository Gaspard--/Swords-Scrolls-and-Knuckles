#include "Fixture.hpp"
#include "SaveGame.hpp"
#include "LoadGame.hpp"

void    Fixture::serialize(SaveState &state) const
{
  state.serialize(pos);
  state.serialize(speed);
}

void    Fixture::unserialize(LoadGame &game)
{
  game.unserialize(pos);
  game.unserialize(speed);
}
