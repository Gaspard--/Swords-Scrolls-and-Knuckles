#ifndef AUDIO_H
# define AUDIO_H

# include <AL/al.h>
# include <AL/alc.h>
# include <map>
# include <AL/alut.h>

template <unsigned int N, class T>
class Vect;

enum class Sounds
{
  NONE,
  BOYAUX1,
  EUUUH1,
};

class Audio
{
private:
  Audio();

  ALCdevice *device;
  std::map<Sounds, ALuint> const sounds;

public:
  ~Audio();

  Audio(Audio const &) = delete;
  Audio &operator=(Audio const &) = delete;

  static Audio &getInstance(void);
  static bool checkError(bool outputError=true);
  static void clearError();
  static unsigned int bufferFromSound(Sounds);

};

#endif /* !AUDIO_H */
