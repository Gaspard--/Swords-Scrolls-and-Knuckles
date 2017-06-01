#ifndef LOGIC_THREAD_HPP
# define LOGIC_THREAD_HPP

#include "Logic.hpp"

class LogicThread
{
private:
  Logic logic;
  std::thread thread;
public:
  LogicThread();
  ~LogicThread();
  Logic *operator->();
  Logic const *operator->() const;
  Logic &operator*();
  Logic const &operator*() const;
};

#endif
