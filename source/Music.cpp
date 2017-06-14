#include <iostream>
#include <thread>
#include "Music.hpp"
#include "AudioError.hpp"

Music::Music(Musics m, float loop)
  : source(AL_NONE), loopTime(loop)
{
  if (ov_fopen(Audio::getMusicFileName(m), &oggStream) < 0)
    throw AudioError("Could not open .ogg file");
  vorbisInfo = ov_info(&oggStream, -1);
  vorbisComment = ov_comment(&oggStream, -1);
  format = vorbisInfo->channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
  alGenSources(1, &source);
  Audio::checkError();
  alGenBuffers(2, buffers.data());
  if (!Audio::checkError(false))
    {
      alDeleteSources(1, &source);
      ov_clear(&oggStream);
      throw AudioError("Couldn't generate a buffer in Music::Music");
    }

  alSource3f(source, AL_POSITION, 0., 0., 0.);
  alSource3f(source, AL_VELOCITY, 0., 0., 0.);
  alSource3f(source, AL_DIRECTION, 0., 0., 0.);
  alSourcef(source, AL_ROLLOFF_FACTOR, 0.);
  alSourcef(source, AL_SOURCE_RELATIVE, AL_TRUE);
  if (!Audio::checkError(false))
    {
      alDeleteSources(1, &source);
      ov_clear(&oggStream);
      alDeleteBuffers(1, &buffers[0]);
      throw AudioError("Couldn't generate a buffer in Music::Music");
    }
}

Music::~Music()
{
  alSourceStop(source);
  unqueuePending();
  alDeleteSources(1, &source);
  alDeleteBuffers(1, &buffers[0]);
  ov_clear(&oggStream);
}

void Music::play(void)
{
  if (!streamFile(buffers[0]) || !streamFile(buffers[1]))
    throw AudioError("Couldn't play music");
  alSourceQueueBuffers(source, 2, buffers.data());
  alSourcePlay(source);
}

void Music::setLoopTime(float f)
{
  loopTime = f;
}

void Music::setVolume(float f) const
{
  alSourcef(source, AL_GAIN, f);
  Audio::checkError();
}

bool Music::isPlaying(void) const
{
  ALenum state;

  alGetSourcei(source, AL_SOURCE_STATE, &state);
  return state == AL_PLAYING;
}
void Music::update(void)
{
  ALuint buffer[1];
  int processed(AL_NONE);
  bool active(true);

  alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);
  if (processed)
    {
      alSourceUnqueueBuffers(source, 1, buffer);
      Audio::checkError();
      active = streamFile(buffer[0]);
      alSourceQueueBuffers(source, 1, buffer);
      Audio::checkError();
      if (!active)
	ov_time_seek(&oggStream, loopTime);
    }
}

bool Music::streamFile(ALuint buffer)
{
  char data[BUFFER_SIZE];
  unsigned int size(0);

  while (size < BUFFER_SIZE)
    {
      int size_read(ov_read(&oggStream, data + size, BUFFER_SIZE - size, 0, 2, 1, 0));
      size += size_read;
      if (size_read <= 0)
	return false;
    }
  alBufferData(buffer, format, data, size, vorbisInfo->rate);
  Audio::checkError();
  return true;
}

void Music::unqueuePending(void)
{
  ALuint buffer(AL_NONE);
  int queued(AL_NONE);

  alGetSourcei(source, AL_BUFFERS_QUEUED, &queued);
  while (queued--)
    {
      alSourceUnqueueBuffers(source, 1, &buffer);
      Audio::checkError();
    }
}
