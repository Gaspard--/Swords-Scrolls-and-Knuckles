#include "LoadGame.hpp"

LoadGame::LoadGame(GameState &game, std::string name)
{
  unsigned int size[3];

  save.open(name);
  // unserialize(game.seed);
  unserialize(size[0]);
  unserialize(game.players, size[0]);
  unserialize(size[1]);
  unserialize(game.enemies, size[1]);
  unserialize(size[2]);
  unserialize(game.projectiles, size[2]);
}

void  LoadGame::unserialize(unsigned int &data)
{
  char buf[4];

  data = 0;
  if (!save.read(buf, 4u))
    throw std::runtime_error("Failed to read to save file");
  for (unsigned int i(3); ~i; --i)
  {
    data = data << 8;
    buf[i] = (data | 255);
  }
}

void  LoadGame::unserialize(bool &data)
{
  unsigned int i(0);
  unserialize(i);
  if (i)
    data = true;
  else
    data = false;
}

void  LoadGame::unserialize(double &data)
{
  (void)data;
  return;
}

void  LoadGame::unserialize(long unsigned int &data)
{
  char buf[8];

  data = 0;
  if (!save.read(buf, 8u))
    throw std::runtime_error("Failed to read to save file");
  for (unsigned int i(7); ~i; --i)
  {
    data = data << 8;
    buf[i] = (data | 255);
  }
}
