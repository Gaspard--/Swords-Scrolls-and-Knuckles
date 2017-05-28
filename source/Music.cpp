#include <iostream>
#include <thread>
#include "Music.hpp"
#include "Audio.hpp"
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
  try
    {
      Audio::checkError();
    }
  catch (AudioError const &)
    {
      alDeleteSources(1, &source);
      throw;
    }
  alSource3f(source, AL_POSITION, 0., 0., 0.);
  alSource3f(source, AL_VELOCITY, 0., 0., 0.);
  alSource3f(source, AL_DIRECTION, 0., 0., 0.);
  alSourcef(source, AL_ROLLOFF_FACTOR, 0.);
  alSourcef(source, AL_SOURCE_RELATIVE, AL_TRUE);
  Audio::checkError();
}

Music::~Music()
{
  alSourceStop(source);
  unqueuePending();
  alDeleteSources(1, &source);
  alDeleteBuffers(1, &buffers[0]);
  ov_clear(&oggStream);
}

bool Music::play(void)
{
  if (!streamFile(buffers[0]) || !streamFile(buffers[1]))
    return false;
  alSourceQueueBuffers(source, 2, buffers.data());
  alSourcePlay(source);
  return true;
}

void Music::setLoopTime(float f)
{
  loopTime = f;
}

bool Music::isPlaying(void) const
{
  ALenum state;

  alGetSourcei(source, AL_SOURCE_STATE, &state);
  return state == AL_PLAYING;
}

void Music::update(void)
{
  ALuint buffer;
  int processed;
  bool active = true;

  alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);
  while (processed--)
    {
      alSourceUnqueueBuffers(source, 1, &buffer);
      Audio::checkError();
      active = streamFile(buffer);
      alSourceQueueBuffers(source, 1, &buffer);
      Audio::checkError();
    }
  if (!active)
    {
      ov_time_seek(&oggStream, loopTime);
      active = true;
    }
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
  Audio::checkError();
  return true;
}

void Music::unqueuePending(void)
{
  int queued;
  ALuint buffer;

  alGetSourcei(source, AL_BUFFERS_QUEUED, &queued);
  while (queued--)
    {
      alSourceUnqueueBuffers(source, 1, &buffer);
      Audio::checkError();
    }
}

/*int main(int argc, char **argv)
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
      std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
    }
  std::cout << "ouais c la f1" << std::endl;
  m.release();
  return (0);
}*/
