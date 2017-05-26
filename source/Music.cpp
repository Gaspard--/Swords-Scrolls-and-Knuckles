#include <iostream>
#include <thread>
#include "Music.hpp"
#include "Audio.hpp"

Music::Music(char const *filename)
  : source(AL_NONE), loopTime(0.f)
{
  init(filename);
}

Music::~Music()
{
  release();
}

bool Music::init(char const *filename)
{
  int result;

  if (source != AL_NONE)
    return false;
  result = ov_fopen(filename, &oggStream);
  if (result < 0)
    {
      std::cerr << "Could not open ogg stream from " << filename << std::endl;
      return false;
    }
  vorbisInfo = ov_info(&oggStream, -1);
  vorbisComment = ov_comment(&oggStream, -1);
  format = vorbisInfo->channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
  ov_time_seek(&oggStream, 155.);
  alGenBuffers(2, buffers.data());
  Audio::checkError();
  alGenSources(1, &source);
  Audio::checkError();
  alSource3f(source, AL_POSITION, 0., 0., 0.);
  alSource3f(source, AL_VELOCITY, 0., 0., 0.);
  alSource3f(source, AL_DIRECTION, 0., 0., 0.);
  alSourcef(source, AL_ROLLOFF_FACTOR, 2.);
  alSourcef(source, AL_SOURCE_RELATIVE, AL_TRUE);
  return true;
}

bool Music::release(void)
{
  Audio::clearError();
  if (source == AL_NONE)
    return false;
  alSourceStop(source);
  unqueuePending();
  alDeleteSources(1, &source);
  source = AL_NONE;
      ALCenum error = alGetError();

      if (error != AL_NO_ERROR)
	{
	  std::cerr << alutGetErrorString(error) << std::endl;
	  return false;
	}
  if (!Audio::checkError())
    return false;
  alDeleteBuffers(1, &buffers[0]);
  if (!Audio::checkError())
    return false;
  ov_clear(&oggStream);
  return true;
}

bool Music::play(void)
{
  if (!streamFile(buffers[0]) || !streamFile(buffers[1]))
    return false;
  alSourceQueueBuffers(source, 2, buffers.data());
  alSourcePlay(source);
  return true;
}

bool Music::isPlaying(void) const
{
  ALenum state;

  alGetSourcei(source, AL_SOURCE_STATE, &state);
  return state == AL_PLAYING;
}

bool Music::update(void)
{
  ALuint buffer;
  int processed;
  bool active = true;

  alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);
  while (processed--)
    {
      alSourceUnqueueBuffers(source, 1, &buffer);
      if (!Audio::checkError())
	return false;
      active = streamFile(buffer);
      alSourceQueueBuffers(source, 1, &buffer);
      if (!Audio::checkError())
	return false;
    }
  if (!active)
    {
      ov_time_seek(&oggStream, loopTime);
      std::cerr << "kek" << std::endl;
      active = true;
    }
  return active;
}

bool Music::streamFile(ALuint buffer)
{
  char data[BUFFER_SIZE];
  int size_read;
  int size = 0;

  while (size < BUFFER_SIZE)
    {
      size_read = ov_read(&oggStream, data + size, BUFFER_SIZE - size, 0, 2, 1, 0);
      size += size_read;
      if (size_read <= 0)
	return false;
    }
  alBufferData(buffer, format, data, size, vorbisInfo->rate);
  return Audio::checkError();
}

bool Music::unqueuePending(void)
{
  int queued;
  ALuint buffer;

  alGetSourcei(source, AL_BUFFERS_QUEUED, &queued);
  while (queued--)
    {
      alSourceUnqueueBuffers(source, 1, &buffer);
      if (!Audio::checkError())
	return false;
    }
  return true;
}

void Music::setLoopTime(float f)
{
  loopTime = f;
}

int main(int argc, char **argv)
{
  if (argc != 2)
    {
      std::cerr << "provide a filename" << std::endl;
      return 1;
    }

  Music m(argv[1]);

  if (!m.play())
    {
      std::cerr << "olala cpjanti lé zerreur" << std::endl;
      return 1;
    }
  for (int i = 0; i < 100; i++)
    {
      m.update();
      if (!m.isPlaying())
	{
	  std::cerr << "mins sa sé arété avan la f1" << std::endl;
	  return 1;
	}
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  std::cout << "ouais c la f1" << std::endl;
  m.release();
  return (0);
}
