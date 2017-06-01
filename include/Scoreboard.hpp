#ifndef SCOREBOARD_HPP_
#define SCOREBOARD_HPP_

#include <sstream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>

struct PlayerData
{
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
};

std::ostream                &operator<<(std::ostream &, PlayerData const &);
std::vector<PlayerData>     lineToPlayerInfo(std::string);

#endif
