#ifndef AUDIOSOURCE_H
# define AUDIOSOURCE_H

# include <AL/al.h>
# include <AL/alc.h>
# include "Audio.hpp"

template <unsigned int N, class T>
class Vect;

class AudioSource
{
private:
  ALuint id;
  ALuint buffer;

public:
  AudioSource(Sounds, Vect<3, float> const &);
  ~AudioSource();

  AudioSource(AudioSource const &) = delete;
  AudioSource &operator=(AudioSource const &) = delete;

  void setPos(Vect<3, float> const &);
  void setLooping(bool) const;
  void setVolume(float) const;
  void play(void) const;
  void stop(void) const;
};

#endif /* !AUDIOSOURCE_H */
