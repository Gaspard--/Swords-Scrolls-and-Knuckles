#ifndef SAVEGAME_HPP
# define SAVEGAME_HPP

# include "GameState.hpp"

class SaveState
{
private:
  std::fstream  file;
  int  seed;
public:
  SaveState() = delete;
  SaveState(GameState, long unsigned int);
  SaveState(SaveState const &) = delete;
  SaveState &operator=(SaveState const &) = delete;
  ~SaveState();

  bool Serialize(unsigned int);
};

#endif
