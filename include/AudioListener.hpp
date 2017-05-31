#ifndef AUDIOLISTENER_HPP
# define AUDIOLISTENER_HPP

template <unsigned int N, class T>
class Vect;

namespace AudioListener
{
  void setPos(Vect<3, float> const &);
  void setVolume(float f);
};

#endif /* !AUDIOLISTENER_HPP */
