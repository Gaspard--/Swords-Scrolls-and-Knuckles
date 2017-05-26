#ifndef AUDIO_H
# define AUDIO_H

# include <AL/al.h>
# include <AL/alc.h>
# include <AL/alut.h>
# include <unordered_map>

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

  static Audio instance;

  ALCdevice *device;
  std::unordered_map<Sounds, ALuint> sounds;
  std::unordered_map<Sounds, char const *> const filenames;

public:
  ~Audio();

  Audio(Audio const &) = delete;
  Audio &operator=(Audio const &) = delete;

  static Audio &getInstance(void);
  static bool checkError(bool outputError=true);
  static void clearError();
  unsigned int bufferFromSound(Sounds);

  /*
  ** Sources using the buffers to be deleted need to release the buffer
  ** for this function to work properly
  */
  bool deleteBuffers(std::initializer_list<Sounds>);

};

#endif /* !AUDIO_H */
