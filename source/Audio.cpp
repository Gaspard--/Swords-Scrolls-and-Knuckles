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
  std::for_each(sounds.cbegin(), sounds.cend(),
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
  ALCenum error = alGetError();

  if (error != AL_NO_ERROR)
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
  if (s == Sounds::NONE)
    return 0;
  auto it = sounds.find(s);

  if (it == sounds.end())
    sounds[s] = alutCreateBufferFromFile(filenames.at(s));
  return sounds.at(s);
}

bool Audio::deleteBuffers(std::initializer_list<Sounds> sndlst)
{
  bool ret = true;

  for (auto s : sndlst)
    {
      auto it = sounds.find(s);
      if (it == sounds.end() || it->second == AL_NONE)
	ret = false;
      else
	{
	  alDeleteBuffers(1, &(it->second));
	  ALCenum error = alGetError();

	  if (error != AL_NO_ERROR)
	    {
	      std::cerr << alutGetErrorString(error) << std::endl;
	      ret = false;
	    }
	  else
	    this->sounds[s] = AL_NONE;
	}
    }
  return ret;
}

/*int main()
{
  Vect<3, float> v {0, 0, 0};
  AudioSource by(Sounds::BOYAUX1, v);
  alDistanceModel(AL_INVERSE_DISTANCE);

  std::cout << Audio::getInstance().deleteBuffers({Sounds::EUUUH1, Sounds::BOYAUX1}) << std::endl;
  //euuh.init(Sounds::EUUUH1, v);
  //std::cout << by.init(Sounds::BOYAUX1, v) << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  std::this_thread::sleep_for(std::chrono::seconds(1));
  by.setPos({0.00001, 0, 0});
  by.play();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  by.setPos({0.6, 0, 0});
  by.play();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  by.setPos({1, 0, 0});
  by.play();
  std::this_thread::sleep_for(std::chrono::seconds(1));
}*/
