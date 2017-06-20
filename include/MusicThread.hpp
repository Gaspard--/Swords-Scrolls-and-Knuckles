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

public:
  std::mutex mutex;

  template<class... PARAMS>
  MusicThread(PARAMS &&... params)
    : go(true)
    , music(std::forward<PARAMS>(params)...)
    , thread([this]() {
	       {
		 std::lock_guard<std::mutex> guard(mutex);
		 music.play();
	       }
	     while ([this]() {
	       std::lock_guard<std::mutex> guard(mutex);

	       music.update();
	       std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
	       return go;
	     }());
      })
  {}

  ~MusicThread();

  Music *operator->();
  Music const *operator->() const;
  Music &operator*();
  Music const &operator*() const;
};

#endif /* !MUSICTHREAD_HPP */
