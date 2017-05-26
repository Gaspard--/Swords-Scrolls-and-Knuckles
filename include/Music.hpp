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
  FILE			*oggFile;
  std::array<ALuint, 2>	buffers;
  ALuint		source;
  ALenum		format;


public:
  Music();

  bool init(char const *);
  bool release(void);
  bool unqueuePending(void);
  bool play(void);
  bool isPlaying(void) const;
  bool update(void);
  bool streamFile(ALuint buffer);
};

#endif /* !MUSIC_H */
