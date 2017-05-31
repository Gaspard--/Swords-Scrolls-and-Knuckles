#include <algorithm>
#include <iostream>
#include <thread>
#include <chrono>
#include "AudioListener.hpp"
#include "AudioSource.hpp"
#include "Audio.hpp"
#include "Music.hpp"
#include "Vect.hpp"
#include "AudioError.hpp"

constexpr std::array<char const *, static_cast<size_t>(Sounds::SIZE)> const Audio::soundFilenames;
constexpr std::array<char const *, static_cast<size_t>(Musics::SIZE)> const Audio::musicFilenames;

Audio Audio::instance;

Audio::Audio()
{
  alutInit(nullptr, nullptr);
  device = alcOpenDevice(nullptr);
  Audio::checkError();
}

Audio::~Audio()
{
  std::for_each(sounds.cbegin(), sounds.cend(),
		[](auto &it) { alDeleteBuffers(1, &it.second); });
  alcCloseDevice(device);
  alutExit();
}

Audio &Audio::getInstance(void)
{
  return instance;
}

bool Audio::checkError(bool throws)
{
  ALCenum error(alGetError());

  if (error != AL_NO_ERROR)
    {
      if (throws)
	throw AudioError(alutGetErrorString(error));
      else
	return false;
    }
  return true;
}

void Audio::clearError(void)
{
  alGetError();
}

ALuint Audio::bufferFromSound(Sounds s)
{
  if (s == Sounds::NONE || s == Sounds::SIZE)
    return 0;
  auto it(sounds.find(s));

  if (it == sounds.end())
    {
      sounds[s] = alutCreateBufferFromFile(Audio::soundFilenames[static_cast<size_t>(s)]);
      Audio::checkError();
    }
  return sounds.at(s);
}

char const *Audio::getMusicFileName(Musics s)
{
  return musicFilenames[static_cast<size_t>(s)];
}

bool Audio::deleteBuffers(std::initializer_list<Sounds> sndlst)
{
  bool ret(true);

  for (auto s : sndlst)
    {
      auto it(sounds.find(s));
      if (it == sounds.end() || it->second == AL_NONE)
	ret = false;
      else
	{
	  alDeleteBuffers(1, &(it->second));
	  if (!Audio::checkError(false))
	    ret = false;
	  else
	    this->sounds[s] = AL_NONE;
	}
    }
  return ret;
}
