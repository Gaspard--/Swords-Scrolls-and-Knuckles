#include "LoadGame.hpp"

LoadGame::LoadGame(GameState &game, SaveState &save)
{
  unserialize(seed);
  unserialize((long unsigned)state.players.size());
  unserialize(state.players);
  unserialize((long unsigned)state.enemies.size());
  unserialize(state.enemies);
  unserialize((long unsigned)state.projectiles.size());
  unserialize(state.projectiles);
}

void  LoadGame::unserialize(unsigned int &data)
{
  unsigned char buf[4];

  data = 0;
  if (!save.file.read(buf, 4u))
    throw std::runtime_error("Failed to read to save file");
  for (unsigned int i(3); ~i; --i)
  {
    data = data << 8;
    buf[i] = (data | 255);
  }
}

void  LoadGame::unserialize(bool &data)
{
  int i(0);
  unserialize(i);
  if (i)
    data = true;
  else
    data = false;
}

void  LoadGame::unserialize(double & data)
{

}
void  LoadGame::unserialize(long unsigned int &)
{
  unsigned char buf[8];

  data = 0;
  if (!save.file.read(buf, 8u))
    throw std::runtime_error("Failed to read to save file");
  for (unsigned int i(7); ~i; --i)
  {
    data = data << 8;
    buf[i] = (data | 255);
  }
}
