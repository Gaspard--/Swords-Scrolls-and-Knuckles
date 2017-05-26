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

public:
  Music(char const *filename);
  ~Music();

  /*
  ** Do not HAVE to be called (but can be)
  ** These are only for memory reasons
  ** to avoid useless destruction/reconstruction of object
  */
  bool init(char const *);
  bool release(void);

  bool unqueuePending(void);
  bool play(void);
  bool isPlaying(void) const;
  bool update(void);
  bool streamFile(ALuint buffer);
  void setLoopTime(float);
};

#endif /* !MUSIC_H */
