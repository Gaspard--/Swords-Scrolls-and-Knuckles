#ifndef AUDIOSOURCE_H
# define AUDIOSOURCE_H

# include "Audio.hpp"

template <unsigned int N, class T>
class Vect;

class AudioSource
{
private:
  ALuint id;
  ALuint buffer;

public:
  AudioSource(Sounds, Vect<3, float> const &pos);
  ~AudioSource();

  AudioSource(AudioSource const &) = delete;
  AudioSource &operator=(AudioSource const &) = delete;

  void play(void) const;
  void stop(void) const;
  void setPos(Vect<3, float> const &) const;
  void setLooping(bool) const;
  void setVolume(float) const;
};

#endif /* !AUDIOSOURCE_H */
