#include "Vect.hpp"
#include "Audio.hpp"
#include "AudioListener.hpp"

namespace AudioListener
{
  void setPos(Vect<3, float> const &v)
  {
    alListener3f(AL_POSITION, v[0], v[1], v[2]);
    Audio::checkError();
  }

  void setVolume(float f)
  {
    alListenerf(AL_GAIN, f);
    Audio::checkError();
  }
}
