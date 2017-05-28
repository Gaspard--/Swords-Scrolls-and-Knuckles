#ifndef AUDIO_H
# define AUDIO_H

# include <AL/al.h>
# include <AL/alc.h>
# include <AL/alut.h>
# include <unordered_map>
# include <array>

template <unsigned int N, class T>
class Vect;

enum class Sounds
{
  NONE,
  BOYAUX1,
  EUUUH1,
  SIZE
};

enum class Musics
{
  NONE,
  SMALL_WORLD,
  SIZE,
};

class Audio
{
private:
  Audio();

  static Audio instance;

  ALCdevice *device;
  std::unordered_map<Sounds, ALuint> sounds;
  static std::array<char const *, static_cast<size_t>(Sounds::SIZE)> const soundFilenames;
  static std::array<char const *, static_cast<size_t>(Musics::SIZE)> const musicFilenames;

public:
  ~Audio();

  Audio(Audio const &) = delete;
  Audio &operator=(Audio const &) = delete;

  static Audio &getInstance(void);
  static bool checkError(bool throws=true);
  static void clearError();
  static char const *getMusicFileName(Musics);
  ALuint bufferFromSound(Sounds);

  /*
  ** Sources using the buffers to be deleted need to release the buffer
  ** for this function to work properly
  */
  bool deleteBuffers(std::initializer_list<Sounds>);

};

#endif /* !AUDIO_H */
