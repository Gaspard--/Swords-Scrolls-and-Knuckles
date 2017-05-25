#include <algorithm>
#include <iostream>
#include <thread>
#include <chrono>
#include "AudioListener.hpp"
#include "AudioSource.hpp"
#include "Audio.hpp"
#include "Vect.hpp"

Audio::Audio()
 : sounds({
      {Sounds::BOYAUX1, alutCreateBufferFromFile("resources/sounds/boyaux1.wav")},
      {Sounds::EUUUH1, alutCreateBufferFromFile("resources/sounds/euuuh1.wav")},
    })
{
  device = alcOpenDevice(nullptr);
}

Audio::~Audio()
{
  Audio &i = Audio::getInstance();
  std::for_each(i.sounds.cbegin(), i.sounds.cend(),
		[](auto &it) { alDeleteBuffers(1, &it.second); });
  alcCloseDevice(device);
  alutExit();
}

Audio &Audio::getInstance(void)
{
  static Audio instance;
  return instance;
}

bool Audio::checkError(bool outputError)
{
  ALCenum error;

  if ((error = alGetError()) != AL_NO_ERROR)
    {
      if (outputError)
	std::cerr << alutGetErrorString(error) << std::endl;
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
  Audio &instance = Audio::getInstance();
  auto it = instance.sounds.find(s);

  if (it == instance.sounds.end())
    return 0;
  return instance.sounds.at(s);
}

int main()
{
  alutInit(nullptr, nullptr);
  AudioSource euuh(Sounds::EUUUH1);
  AudioSource by(Sounds::BOYAUX1);

  by.play();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  by.setPos({1, 0, 0});
  by.play();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  by.setPos({1, 1, 0});
  by.play();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  by.setPos({1, -1, 0});
  by.play();
  std::this_thread::sleep_for(std::chrono::seconds(1));
}
