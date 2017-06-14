#ifndef AUDIOSOURCE_HPP
# define AUDIOSOURCE_HPP

# include "Audio.hpp"
# include "Vect.hpp"

class AudioSource
{
private:
  ALuint id;
  ALuint buffer;

public:
  AudioSource(Sounds, Vect<3, float> const &pos={0, 0, 0});
  ~AudioSource();

  AudioSource(AudioSource const &) = delete;
  AudioSource &operator=(AudioSource const &) = delete;

  void play(void) const;
  void stop(void) const;
  void setPos(Vect<3, float> const &) const;
  void setLooping(bool) const;
  void setVolume(float) const;
  void setGlobal(bool) const;
};

#endif /* !AUDIOSOURCE_HPP */
