#ifndef LOGIC_HPP
# define LOGIC_HPP

#include <mutex>
#include <thread>
#include <chrono>

class LevelScene;

// GNU Collaborative International Dictionary of English
class Logic
{
private:
  using Clock = std::conditional<std::chrono::high_resolution_clock::is_steady,
				 std::chrono::high_resolution_clock,
				 std::chrono::steady_clock>::type;
  std::mutex lock;
  std::chrono::time_point<Clock> last_update;
  bool stop;  
  bool tick();

public:
  Logic();
  void run();
  void exit();
  void updateDisplay(LevelScene &);
};

#endif
