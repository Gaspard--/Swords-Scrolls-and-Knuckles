#include <iostream>
#include <ctime>
#include "Controllable.hpp"
#include "SaveGame.hpp"

SaveState::SaveState (GameState &state, long unsigned int i)
: file([](){
  time_t           t;
  struct tm        *timeinfo;

  time(&t);
  timeinfo = localtime(&t);
  return (asctime(timeinfo));
}())
{
  seed = i;
  if (!file)
    throw std::runtime_error("Failed to open file stream");
  serialize(seed);
  serialize((long unsigned)state.players.size());
  serialize(state.players);
  serialize((long unsigned)state.enemies.size());
  serialize(state.enemies);
  serialize((long unsigned)state.projectiles.size());
  serialize(state.projectiles);
}

void    SaveState::serialize(unsigned int data)
{
  unsigned char c[4];

  for (unsigned int i(0); i < 4; ++i)
  {
    c[i] = (data & 255);
    data = data >> 8;
  }
  if (!file.write((const char *)c, 4u))
    throw std::runtime_error("Failed to write to save file");
}

void    SaveState::serialize(bool data)
{
  if (data)
    serialize(1u);
  else
    serialize(0u);
}

void    SaveState::serialize(long unsigned int data)
{
  unsigned char c[8];

  for (unsigned int i(0); i < 8; ++i)
  {
    c[i] = (data & 255);
    data = data >> 8;
  }
  if (!file.write((const char *)c, 8u))
    throw std::runtime_error("Failed to write to save file");
}

void    SaveState::serialize(double f)
{
  unsigned int bits = 53;
  unsigned int expbits = 11;
  double fnorm;
  int shift;
  unsigned long sign, exp, significand;
  unsigned int significandbits = bits - expbits - 1; // -1 for sign bit

  if (f == 0.0) // get this special case out of the way
    return ;
  if (f < 0)// check sign and begin normalization
  {
    sign = 1;
    fnorm = -f;
  }
  else
  {
    sign = 0;
    fnorm = f;
  }
  shift = 0; // get the normalized form of f and track the exponent
  while(fnorm >= 2.0)
  {
    fnorm /= 2.0;
    shift++;
  }
  while(fnorm < 1.0)
  {
    fnorm *= 2.0;
    shift--;
  }
  fnorm = fnorm - 1.0;
  significand = fnorm * ((1LL<<significandbits) + 0.5f); // calculate the binary form (non-float) of the significand data
  exp = shift + ((1<<(expbits-1)) - 1); // get the biased exponent shift + bias
  serialize((sign<<(bits-1)) | (exp<<(bits-expbits-1)) | significand);
}
