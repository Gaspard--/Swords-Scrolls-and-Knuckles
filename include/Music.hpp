#ifndef MUSIC_H
# define MUSIC_H

# include <array>
# include <ogg/ogg.h>
# include <vorbis/codec.h>
# include <vorbis/vorbisfile.h>
# include <vorbis/vorbisenc.h>
# include "al.h"
# include "alc.h"
# include "alut.h"

# define BUFFER_SIZE (4096 * 8)

enum class Musics;

class Music
{
private:
  OggVorbis_File	oggStream;
  vorbis_info		*vorbisInfo;
  vorbis_comment	*vorbisComment;
  std::array<ALuint, 2>	buffers;
  ALuint		source;
  ALenum		format;
  float			loopTime;

  void unqueuePending(void);
  bool streamFile(ALuint buffer);

public:
  Music(Musics m, float loopTime=0.);
  ~Music();

  Music(Music const &) = delete;
  Music &operator=(Music const &) = delete;

  /*
  ** Returns false if the music could not be played
  */
  bool play(void);

  /*
  ** To be called regularly (since the file is read a chunk at a time)
  */
  void update(void);

  bool isPlaying(void) const;
  void setLoopTime(float);
};

#endif /* !MUSIC_H */
