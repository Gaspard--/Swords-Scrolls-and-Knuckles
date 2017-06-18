#include "GameState.hpp"
#include "SaveGame.hpp"

class LoadGame
{
private:
  std::fstream  save;

public:
  LoadGame() = delete;
  LoadGame(GameState &, std::string);
  LoadGame(GameState const &) = delete;
  LoadGame &operator=(GameState const &) = delete;
  ~LoadGame();

  void  unserialize() = delete;
  void  unserialize(unsigned int &);
  void  unserialize(bool &);
  void  unserialize(long unsigned int &);
  void  unserialize(double &);

  template<unsigned int SIZE, class T>
  void    unserialize(Vect<SIZE, T> &data);

  template<class T>
  void    unserialize(std::vector<T> &data, unsigned int);
};

template<unsigned int SIZE, class T>
void    LoadGame::unserialize(Vect<SIZE, T> &data)
{
  for (auto &&t : data)
    unserialize(t);
}

template<class T>
void    LoadGame::unserialize(std::vector<T> &data, unsigned int size)
{
  data.resize(size);
  for (auto &t : data)
    t.unserialize(*this);
}
