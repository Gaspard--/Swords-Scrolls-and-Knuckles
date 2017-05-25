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

  /*
  ** Do not HAVE to be called (but can be)
  ** These are only for memory reasons
  ** to avoid useless destruction/reconstruction of object
  ** (eg: release when too far and init when coming up closer)
  */
  bool init(Sounds, Vect<3, float> const &);
  bool release();

  bool setPos(Vect<3, float> const &);
  bool setLooping(bool) const;
  bool setSound(Sounds);
  bool setVolume(float) const;
  bool play(void) const;
  bool stop(void) const;
};

#endif /* !AUDIOSOURCE_H */
