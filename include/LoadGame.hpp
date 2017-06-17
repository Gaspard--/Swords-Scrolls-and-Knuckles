#include "GameState.hpp"
#include "SaveGame.hpp"

class LoadGame
{
  LoadGame() = delete;
  LoadGame(GameState &, SaveState &);
  LoadGame(GameState const &) = delete;
  LoadGame &operator=(GameState const &) = delete;
  ~LoadGame();

  void  unserialize() = delete;
  void  unserialize(unsigned int &);
  void  unserialize(bool &);
  void  unserialize(long unsigned int &);
  void  unserialize(double &);

  template<unsigned int SIZE, class T>
  void    unserialize(Vect<SIZE, T> data);

  template<class T>
  void    unserialize(std::vector<T> const &data);
};

template<unsigned int SIZE, class T>
void    LoadGame::unserialize(Vect<SIZE, T> data)
{
  for (auto &&t : data)
    unserialize(t);
}

template<class T>
void    LoadGame::unserialize(std::vector<T> const &data)
{
  for (auto const &t : data)
    t.unserialize(*this);
}
