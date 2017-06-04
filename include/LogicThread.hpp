#ifndef LOGIC_THREAD_HPP
# define LOGIC_THREAD_HPP

#include "Logic.hpp"

class LogicThread
{
private:
  Logic logic;
  std::thread thread;
public:
  template<class... PARAMS>
  LogicThread(PARAMS &&... params)
    : logic(std::forward<PARAMS>(params)...)
    , thread([this](){
	logic.run();
      })
  {}

  ~LogicThread();
  Logic *operator->();
  Logic const *operator->() const;
  Logic &operator*();
  Logic const &operator*() const;
};

#endif
