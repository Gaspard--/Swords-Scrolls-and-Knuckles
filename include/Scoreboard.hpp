#ifndef SCOREBOARD_HPP_
#define SCOREBOARD_HPP_

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>

class PlayerData
{
public:
  bool            isScore;
  std::string     playerName;
  std::string     playerClass;
  int             playerScore;

  PlayerData(std::string);
  ~PlayerData() = default;
};

class Scoreboard
{
private:
  std::vector<std::vector<PlayerData>> scoreboard;

public:
  void  sort(void);
  void  loadDataFromFile(std::string);
  void  dumpInfo(std::string);
  //une fonction qui ajoute
};

std::ostream                &operator<<(std::ostream &, PlayerData &);
std::vector<PlayerData>     lineToPlayerInfo(std::string);

#endif
