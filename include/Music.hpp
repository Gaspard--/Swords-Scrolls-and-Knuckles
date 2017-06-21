#ifndef MUSIC_HPP
# define MUSIC_HPP

# include <array>
# include <mutex>

# include <ogg/ogg.h>
# include <vorbis/codec.h>
# include <vorbis/vorbisfile.h>
# include <vorbis/vorbisenc.h>
# include "al.h"
# include "alc.h"
# include "alut.h"
# include "Audio.hpp"

class Music
{
private:
  static constexpr unsigned int BUFFER_SIZE = 4096 * 8;
  OggVorbis_File oggStream;
  vorbis_info *vorbisInfo;
  vorbis_comment *vorbisComment;
  std::array<ALuint, 2>	buffers;
  ALuint source;
  ALenum format;
  Musics music;
  float	loopTime;
  bool fade;

  void unqueuePending(void);
  bool streamFile(ALuint buffer);
  void initMusic(Musics m, float loopTime);
  void releaseMusic(void);

public:
  Music(Musics m, float loopTime=0.f);
  ~Music();

  Music(Music const &) = delete;
  Music &operator=(Music const &) = delete;
  std::mutex mutex;

  void play(void);

  /*
  ** To be called regularly (since the file is read a chunk at a time)
  */
  void update(void);

  void setMusic(Musics, float loopTime=0.f);
  bool isPlaying(void) const;
  void setLoopTime(float);
  void setVolume(float) const;
  float getVolume(void) const;
  void setFade(bool);
  void fadeTo(Musics);
};

#endif /* !MUSIC_HPP */
