#include <iostream>
#include "AudioSource.hpp"
#include "Vect.hpp"

AudioSource::AudioSource(Sounds sound, Vect<3, float> const &pos,
			 Vect<3, float> const &speed)
  :  buffer(AL_NONE)
{
  alGenSources(1, &id);
  Audio::checkError();
  alSourcef(id, AL_PITCH, 1);
  Audio::checkError();
  alSourcef(id, AL_GAIN, 1);
  Audio::checkError();
  setSound(sound);
  Audio::checkError();
  setPos(pos);
  setSpeed(speed);
}

AudioSource::~AudioSource()
{
  alSourcei(id, AL_BUFFER, 0);
  alDeleteSources(1, &id);
}

bool AudioSource::setPos(Vect<3, float> const &v)
{
  alSource3f(id, AL_POSITION, v[0], v[1], v[2]);
  return !Audio::checkError();
}

bool AudioSource::setSpeed(Vect<3, float> const &v)
{
  alSource3f(id, AL_VELOCITY, v[0], v[1], v[2]);
  return !Audio::checkError();
}

bool AudioSource::setLooping(bool b) const
{
  alSourcei(id, AL_LOOPING, b);
  return !Audio::checkError();
}

bool AudioSource::setSound(Sounds s)
{
  buffer = Audio::bufferFromSound(s);
  if (buffer == 0)
    return false;
  alSourcei(id, AL_BUFFER, buffer);
  return !Audio::checkError();
}

bool AudioSource::play(void) const
{
  alSourcePlay(id);
  return !Audio::checkError();
}
