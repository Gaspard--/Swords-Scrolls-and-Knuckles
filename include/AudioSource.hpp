#ifndef AUDIOSOURCE_HPP
# define AUDIOSOURCE_HPP

# include <vector>
# include "OgreVector3.h"
# include "Audio.hpp"


class AudioSource
{
private:
  ALuint id;
  ALuint buffer;

  static std::vector<AudioSource> indeSources;

  void init();

public:
  AudioSource();
  ~AudioSource();

  AudioSource(AudioSource const &) = delete;
  AudioSource &operator=(AudioSource const &) = delete;

  AudioSource(AudioSource &&);
  AudioSource &operator=(AudioSource &&);

  void play(void) const;
  void stop(void) const;
  void setPos(Ogre::Vector3 const &) const;
  void setLooping(bool) const;
  void setSound(Sounds);
  void setVolume(float) const;
  void setGlobal(bool) const;
  bool isPlaying(void) const;

  static void playIndependentSound(Sounds, bool global=true,
				    Ogre::Vector3 const &pos={0, 0, 0}, float volume=100.f);
  static void removeFinishedIndeSounds(void);
};

#endif /* !AUDIOSOURCE_HPP */
