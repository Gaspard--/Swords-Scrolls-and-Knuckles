#include "Enemy.hpp"
#include "SaveGame.hpp"
#include "LoadGame.hpp"

void    Enemy::serialize(SaveState &state) const
{
  state.serialize(ai);
}

void   Enemy::unserialize(LoadGame &game)
{
  game.unserialize(ai);
}
