#ifndef AUDIOLISTENER_HPP
# define AUDIOLISTENER_HPP

namespace Ogre { class Vector3; };

template <unsigned int N, class T>
class Vect;

namespace AudioListener
{
  void setPos(Ogre::Vector3 const &);
  void setVolume(float f);
};

#endif /* !AUDIOLISTENER_HPP */
