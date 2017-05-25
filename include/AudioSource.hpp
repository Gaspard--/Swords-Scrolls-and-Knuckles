#ifndef AUDIOSOURCE_H
# define AUDIOSOURCE_H

# include <AL/al.h>
# include <AL/alc.h>
# include "Vect.hpp"
# include "Audio.hpp"

template <unsigned int N, class T>
class Vect;

class AudioSource
{
private:
  ALuint id;
  ALuint buffer;

public:
  AudioSource(Sounds=Sounds::NONE,
	      Vect<3, float> const &pos={0, 0, 0});
  ~AudioSource();

  bool setPos(Vect<3, float> const &);
  bool setLooping(bool) const;
  bool setSound(Sounds);
  bool play(void) const;
  bool stop(void) const;
};

#endif /* !AUDIOSOURCE_H */
