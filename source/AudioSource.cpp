#include <iostream>
#include "AudioSource.hpp"
#include "AudioError.hpp"
#include "Vect.hpp"

AudioSource::AudioSource(Sounds sound, Vect<3, float> const &pos)
  :  id(AL_NONE), buffer(AL_NONE)
{
  alGenSources(1, &id);
  Audio::checkError();
  try
    {
      buffer = Audio::getInstance().bufferFromSound(sound);
    }
  catch (AudioError const &)
    {
      alDeleteSources(1, &id);
      throw;
    }
  alSourcei(id, AL_BUFFER, buffer);
  alSourcef(id, AL_PITCH, 1);
  alSourcef(id, AL_GAIN, 1);
  setPos(pos);
  alSourcef(id, AL_ROLLOFF_FACTOR, 2.);
  alSourcef(id, AL_MAX_DISTANCE, 3.);
  alSourcef(id, AL_REFERENCE_DISTANCE, 0.2);
  if (!Audio::checkError(false))
    {
      alDeleteSources(1, &id);
      alDeleteBuffers(1, &buffer);
      throw AudioError("Error in AudioSource::AudioSource");
    }
}

AudioSource::~AudioSource()
{
  stop();
  alSourcei(id, AL_BUFFER, AL_NONE);
  alDeleteSources(1, &id);
}

void AudioSource::setPos(Vect<3, float> const &v) const
{
  alSource3f(id, AL_POSITION, v[0], v[1], v[2]);
  Audio::checkError();
}

void AudioSource::setLooping(bool b) const
{
  alSourcei(id, AL_LOOPING, b);
  Audio::checkError();
}

void AudioSource::setVolume(float f) const
{
  alSourcef(id, AL_GAIN, f);
  Audio::checkError();
}

void AudioSource::play(void) const
{
  alSourcePlay(id);
  Audio::checkError();
}

void AudioSource::stop(void) const
{
  alSourceStop(id);
  Audio::checkError();
}
