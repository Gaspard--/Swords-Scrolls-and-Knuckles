#ifndef AUDIOSOURCE_HPP
# define AUDIOSOURCE_HPP

# include "Audio.hpp"

namespace Ogre { class Vector3; };

class AudioSource
{
private:
  ALuint id;
  ALuint buffer;

  void init();

public:
  AudioSource();
  ~AudioSource();

  AudioSource(AudioSource const &) = delete;
  AudioSource &operator=(AudioSource const &) = delete;

  void play(void) const;
  void stop(void) const;
  void setPos(Ogre::Vector3 const &) const;
  void setLooping(bool) const;
  void setSound(Sounds);
  void setVolume(float) const;
  void setGlobal(bool) const;
  bool isPlaying(void) const;
};

#endif /* !AUDIOSOURCE_HPP */
