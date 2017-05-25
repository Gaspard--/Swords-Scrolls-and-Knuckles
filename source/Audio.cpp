#include <algorithm>
#include <iostream>
#include <thread>
#include <chrono>
#include "AudioListener.hpp"
#include "AudioSource.hpp"
#include "Audio.hpp"
#include "Vect.hpp"

Audio Audio::instance;

Audio::Audio()
 : filenames({
	 {Sounds::BOYAUX1, "resources/sounds/boyaux1.wav"},
	 {Sounds::EUUUH1, "resources/sounds/euuuh1.wav"}
 })
{
  alutInit(nullptr, nullptr);
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
  auto it = sounds.find(s);

  if (it == sounds.end())
    sounds[s] = alutCreateBufferFromFile(filenames.at(s));
  return sounds.at(s);
}

int main()
{
  AudioSource euuh(Sounds::EUUUH1);
  AudioSource by(Sounds::BOYAUX1);
  Vect<3, float> v {0, 0, 0};

  alDistanceModel(AL_INVERSE_DISTANCE);

  while (1)
    {
      by.setPos(v);
      v[0] += 0.02;
      by.play();
      printf("%g\n", v[0]);
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  /*by.setPos({0.00001, 0, 0});
  by.play();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  by.setPos({0.6, 0, 0});
  by.play();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  by.setPos({1, 0, 0});
  by.play();
  std::this_thread::sleep_for(std::chrono::seconds(1));*/
}
