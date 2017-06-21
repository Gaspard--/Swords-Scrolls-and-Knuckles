#include "MusicThread.hpp"

// MusicThread MusicThread::instance(Musics::FIND_YOU);

MusicThread::~MusicThread()
{
  go = false;
  thread.join();
}

MusicThread &MusicThread::getInstance(void)
{
  static MusicThread instance(Musics::FIND_YOU);

  return instance;
}

Music *MusicThread::operator->()
{
  return &music;
}

Music const *MusicThread::operator->() const
{
  return &music;
}

Music &MusicThread::operator*()
{
  return music;
}

Music const &MusicThread::operator*() const
{
  return music;
}
