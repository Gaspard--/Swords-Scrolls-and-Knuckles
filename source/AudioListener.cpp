#include <AL/al.h>
#include "Audio.hpp"
#include "Vect.hpp"
#include "AudioListener.hpp"

AudioListener::AudioListener(Vect<3, float> const &pos)
{
  setPos(pos);
}

void AudioListener::setPos(Vect<3, float> const &v)
{
  alListener3f(AL_POSITION, v[0], v[1], v[2]);
  Audio::checkError();
}

void AudioListener::setVolume(float f)
{
  alListenerf(AL_GAIN, f);
  Audio::checkError();
}
