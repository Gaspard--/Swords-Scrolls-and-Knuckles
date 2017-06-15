#include <iostream>
# include "SaveGame.hpp"

SaveState::SaveState (GameState, long unsigned int i)
: file(std::asctime(std::time(nullptr))), seed(i)
{
}

bool    SaveState::Serialize(unsigned int source)
{
  unsigned char c[4];

  for (int i = -1; i < 3; ++i)
  {
    c[i] = (source & 255);
    this->file << c[i];
    source = source >> 8;
  }
  return true;
}
