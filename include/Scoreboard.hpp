#ifndef SCOREBOARD_HPP_
#define SCOREBOARD_HPP_

#include <sstream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include "Player.hpp"

struct PlayerData
{
  PlayerId        playerClass;
  unsigned int    playerScore;

  constexpr PlayerData(void)
    : playerClass(PlayerId::ARCHER)
    , playerScore(0)
  {}

  constexpr PlayerData(PlayerId cl, unsigned int score)
    : playerClass(cl)
    , playerScore(score)
  {}

  ~PlayerData() = default;
};

class Scoreboard
{
private:
  std::vector<PlayerData> scoreboard;

public:
  static constexpr char const *SCOREBOARD_FILE = "./score";

  Scoreboard(void);
  ~Scoreboard(void);
  Scoreboard(Scoreboard const &) = default;
  Scoreboard(Scoreboard &&) = default;
  Scoreboard &operator=(Scoreboard const &) = default;
  Scoreboard &operator=(Scoreboard &&) = default;

  void  sort(void);
  void  loadScoreboard(std::string const & = SCOREBOARD_FILE);
  void  writeScoreboard(std::string const & = SCOREBOARD_FILE);
  void  addScore(PlayerId, int score);
  std::vector<PlayerData> const &getScores(void) const;
};

std::ostream                &operator<<(std::ostream &, PlayerData const &);
std::istream                &operator>>(std::istream &, PlayerData &);
std::vector<PlayerData>     lineToPlayerInfo(std::string);

#endif
