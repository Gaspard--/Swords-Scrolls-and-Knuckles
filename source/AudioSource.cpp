#include <algorithm>
#include <iostream>
#include "AudioSource.hpp"
#include "AudioError.hpp"

std::vector<AudioSource> AudioSource::indeSources;

AudioSource::AudioSource()
  :  id(AL_NONE), buffer(AL_NONE)
{
}

AudioSource::~AudioSource()
{
  if (id != AL_NONE)
    {
      stop();
      alSourcei(id, AL_BUFFER, AL_NONE);
      alDeleteSources(1, &id);
    }
}

AudioSource::AudioSource(AudioSource &&o)
     : id(o.id), buffer(o.buffer)
{
  o.id = AL_NONE;
  o.buffer = AL_NONE;
}

AudioSource &AudioSource::operator=(AudioSource &&o)
{
  std::swap(buffer, o.buffer);
  std::swap(id, o.id);
  return *this;
}

void AudioSource::init()
{
  alGenSources(1, &id);
  Audio::checkError();
  alSourcef(id, AL_ROLLOFF_FACTOR, 25);
  alSourcef(id, AL_GAIN, 50);
  alSourcef(id, AL_REFERENCE_DISTANCE, 1);
  alSourcef(id, AL_MAX_DISTANCE, 100);
}

void AudioSource::setSound(Sounds sound)
{
  if (id == AL_NONE)
    init();
  if (buffer)
    {
      alSourcei(id, AL_BUFFER, AL_NONE);
      alDeleteSources(1, &id);
    }
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
  if (!Audio::checkError(false))
    {
      alDeleteSources(1, &id);
      alDeleteBuffers(1, &buffer);
      throw AudioError("Error in AudioSource::AudioSource");
    }
}

void AudioSource::setPos(Ogre::Vector3 const &v) const
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

void AudioSource::setGlobal(bool b) const
{
  alSourcef(id, AL_SOURCE_RELATIVE, b);
  Audio::checkError();
}

bool AudioSource::isPlaying(void) const
{
  ALenum state;

  alGetSourcei(id, AL_SOURCE_STATE, &state);
  return state == AL_PLAYING;
}

void AudioSource::playIndependentSound(Sounds sound, bool global,
					       Ogre::Vector3 const &pos,
					       float volume)
{
  indeSources.emplace_back();
  indeSources.back().setSound(sound);
  indeSources.back().setGlobal(global);
  indeSources.back().setPos(pos);
  indeSources.back().setVolume(volume);
  indeSources.back().play();
}

void AudioSource::removeFinishedIndeSounds(void)
{
  indeSources.erase(std::remove_if(indeSources.begin(), indeSources.end(),
				  [](AudioSource &as) { return !as.isPlaying(); }),
		   indeSources.end());
}
