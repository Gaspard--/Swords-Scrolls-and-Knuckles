#include <iostream>
# include "SaveGame.hpp"

SaveState::SaveState (GameState, long unsigned int i)
: file(std::asctime(std::time(nullptr))), seed(i)
{
  if (!file)
    throw std::runtime_error("Failed to open file stream");
  Serialize(seed);
  Serialize();
}

void    SaveState::Serialize(unsigned int data)
{
  unsigned char c[4];

  for (unsigned int i(0); i < 4; ++i)
  {
    c[i] = (data & 255);
    file << c[i];
    data = data >> 8;
  }
  if (!file.write(c, 4u))
    throw std::runtime_error("Failed to write to save file");
}

// #define pack754_32(f) (pack754((f), 32, 8))
// #define pack754_64(f) (pack754((f), 64, 11))

void SaveState::Serialize(long double f, unsigned bits, unsigned expbits)
{
  long double fnorm;
  int shift;
  long long sign, exp, significand;
  unsigned significandbits = bits - expbits - 1; // -1 for sign bit

  if (f == 0.0) // get this special case out of the way
    return 0;
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
  file.write((sign<<(bits-1)) | (exp<<(bits-expbits-1)) | significand);
}
//faire un serialize par primitif
