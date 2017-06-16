#ifndef SAVEGAME_HPP
# define SAVEGAME_HPP

# include "GameState.hpp"

class SaveState
{
private:
  std::ofstream  file;
  int  seed;
  Vect<unsigned int, unsigned int> vectsize;
public:
  SaveState() = delete;
  SaveState(GameState, long unsigned int);
  SaveState(SaveState const &) = delete;
  SaveState &operator=(SaveState const &) = delete;
  ~SaveState();

  void Serialize(unsigned int);
  void Serialize(long double, unsigned, unsigned);
};

template<unsigned int SIZE, class T>
void    SaveState::Serialize(Vect<SIZE, T> data)
{
  for (auto &&t : data)
    Serialize(t);
}

#endif
