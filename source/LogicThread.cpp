#include "LogicThread.hpp"

LogicThread::LogicThread()
  : logic{}
  , thread([this](){
      logic.run();
    })
{}

LogicThread::~LogicThread()
{
  logic.exit();
  thread.join();
}

Logic *LogicThread::operator->()
{
  return &logic;
}

Logic const *LogicThread::operator->() const
{
  return &logic;
}

Logic &LogicThread::operator*()
{
  return logic;
}

Logic const &LogicThread::operator*() const
{
  return logic;
}
