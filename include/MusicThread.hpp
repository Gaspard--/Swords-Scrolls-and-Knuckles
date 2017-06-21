#ifndef MUSICTHREAD_HPP
# define MUSICTHREAD_HPP

# include <iostream>
# include <thread>
# include <mutex>
# include "Music.hpp"

class MusicThread
{
private:
  bool go;
  Music music;
  std::thread thread;

  template<class... PARAMS>
  MusicThread(PARAMS &&... params)
    : go(true)
    , music(std::forward<PARAMS>(params)...)
    , mutex()
    , thread{}
  {
    std::lock_guard<std::mutex> lg(mutex);

    thread = std::thread([this]() {
      std::cout << "IN THREAD" << std::endl;
      {
	std::lock_guard<std::mutex> guard(mutex);

	music.setVolume(0.02f);
	music.play();
      }
      while ([this]() {
	std::lock_guard<std::mutex> guard(mutex);

	music.update();
	std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
	return go;
      }());
    });
  }

public:
  std::mutex mutex;

  ~MusicThread();

  Music *operator->();
  Music const *operator->() const;
  Music &operator*();
  Music const &operator*() const;

  static MusicThread &getInstance(void);
};

#endif /* !MUSICTHREAD_HPP */
