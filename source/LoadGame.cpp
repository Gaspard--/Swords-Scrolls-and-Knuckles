#include "LoadGame.hpp"

LoadGame::LoadGame(GameState &game, std::string name)
{
  unsigned int size[3];

  save.open(name);
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
  unsigned int bits = 53;
  unsigned int expbits = 11;
  unsigned int significandbits = bits - expbits - 1;
  long unsigned int n(0);

  unserialize(n);
  unsigned long sign(n >> (bits - 1));
  n ^= sign << (bits - 1);
  unsigned long exp(n >> (bits - expbits - 1));
  n ^= exp << (bits - expbits - 1);
  double fnorm(n / ((1LL << significandbits) + 0.5f));
  unsigned long shift(exp - ((1 << (expbits-1)) - 1));
  fnorm = ldexp(fnorm, shift);
  if (sign)
    fnorm = -fnorm;
  data = fnorm;
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
    buf[i] = static_cast<char>(data | 255);
  }
}
