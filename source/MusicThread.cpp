#include "MusicThread.hpp"

MusicThread::~MusicThread()
{
  go = false;
  thread.join();
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
