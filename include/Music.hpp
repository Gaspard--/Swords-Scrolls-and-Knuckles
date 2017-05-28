#ifndef MUSIC_H
# define MUSIC_H

# include <AL/al.h>
# include <AL/alc.h>
# include <AL/alut.h>
# include <ogg/ogg.h>
# include <vorbis/codec.h>
# include <vorbis/vorbisfile.h>
# include <vorbis/vorbisenc.h>
# include <array>

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
  Music(Musics m, float loop=0);
  ~Music();

  Music(Music const &) = delete;
  Music &operator=(Music const &) = delete;

  bool play(void);
  void update(void);
  bool isPlaying(void) const;
  void setLoopTime(float);
};

#endif /* !MUSIC_H */
