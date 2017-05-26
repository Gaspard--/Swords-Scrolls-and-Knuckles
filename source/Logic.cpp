#include <iostream>
#include "Logic.hpp"
#include "LevelScene.hpp"

bool Logic::tick()
{
  std::lock_guard<std::mutex> const lock_guard(lock);
  std::cout << "[Logic] tick" << std::endl;
  return stop;
}

Logic::Logic()
  : stop(false)
{
}

void Logic::exit()
{
  std::lock_guard<std::mutex> const lock_guard(lock);

  stop = true;
  std::cout << "[Logic] stoping thread" << std::endl;
}

void Logic::run()
{
  constexpr std::chrono::microseconds TICK_TIME{83333};

  last_update = Clock::now();
  while (!tick())
    {
      auto now = Clock::now();
      if (now > last_update + TICK_TIME * 3) // run is playing catchup by at leaset 3 frames
	last_update = now;
      std::this_thread::sleep_until(last_update += TICK_TIME);
    }
  std::cout << "[Logic] thread exiting" << std::endl;
}

void Logic::updateDisplay(LevelScene &levelScene)
{
  std::lock_guard<std::mutex> const lock_guard(lock);

  // TODO
}
