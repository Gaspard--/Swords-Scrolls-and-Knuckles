#ifndef SAVEGAME_HPP
# define SAVEGAME_HPP

# include <fstream>
# include <vector>
# include "GameState.hpp"

class SaveState
{
private:
  std::ofstream  file;
  unsigned int   seed;

public:
  SaveState() = delete;
  SaveState(GameState &, long unsigned int);
  SaveState(SaveState const &) = delete;
  SaveState(SaveState &&) = delete;
  SaveState &operator=(SaveState const &) = delete;
  SaveState &operator=(SaveState &&) = delete;
  ~SaveState() = default;

  void    serialize(unsigned int);
  void    serialize(double);
  void    serialize(long unsigned int);
  void    serialize(bool);

  template<unsigned int SIZE, class T>
  void    serialize(Vect<SIZE, T> data);

  template<class T>
  void    serialize(std::vector<T> const &data);
};

template<unsigned int SIZE, class T>
void    SaveState::serialize(Vect<SIZE, T> data)
{
  for (auto &&t : data)
    serialize(t);
}

template<class T>
void    SaveState::serialize(std::vector<T> const &data)
{
  for (auto const &t : data)
    t.serialize(*this);
}

#endif
