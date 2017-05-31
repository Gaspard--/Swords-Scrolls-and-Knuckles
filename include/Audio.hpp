#ifndef AUDIO_H
# define AUDIO_H

# include <AL/al.h>
# include <AL/alc.h>
# include <AL/alut.h>
# include <unordered_map>
# include <array>

template <unsigned int N, class T>
class Vect;

/*
** If you want to add sounds/musics, just add an element in the corresponding enum below,
** (between NONE and SIZE, these must remain at beginning/end respectively)
** and fill the corresponding std::array in source/Audio.cpp with the file name.
** (The filenames and the elements in the enums must be in the same order)
*/

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
