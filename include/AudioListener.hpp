#ifndef AUDIOLISTENER_H
# define AUDIOLISTENER_H

template <unsigned int N, class T>
class Vect;

class AudioListener
{
public:
  AudioListener(Vect<3, float> const &);

  void setPos(Vect<3, float> const &) const;
  void setVolume(float f) const;
};

#endif /* !AUDIOLISTENER_H */
