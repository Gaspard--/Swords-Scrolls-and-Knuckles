#include "Vect.hpp"
#include "Audio.hpp"
#include "AudioListener.hpp"

AudioListener::AudioListener(Vect<3, float> const &pos)
{
  setPos(pos);
}

void AudioListener::setPos(Vect<3, float> const &v) const
{
  alListener3f(AL_POSITION, v[0], v[1], v[2]);
  Audio::checkError();
}

void AudioListener::setVolume(float f) const
{
  alListenerf(AL_GAIN, f);
  Audio::checkError();
}
