#include "Fixture.hpp"
#include "SaveGame.hpp"

void    Fixture::serialize(SaveState &state) const
{
  state.serialize(pos);
  state.serialize(speed);
}
