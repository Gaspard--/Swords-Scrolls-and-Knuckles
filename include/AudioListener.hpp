#ifndef AUDIOLISTENER_H
# define AUDIOLISTENER_H

template <unsigned int N, class T>
class Vect;

class AudioListener
{
public:
  AudioListener(Vect<3, float> const &);

  void setPos(Vect<3, float> const &);
  void setVolume(float f);
};

#endif /* !AUDIOLISTENER_H */
