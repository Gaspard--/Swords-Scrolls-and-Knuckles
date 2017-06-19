#include <iostream>
#include <fstream>
#include "Scoreboard.hpp"

// PlayerData

std::ostream    &operator<<(std::ostream &stream, PlayerData const &data)
{
  stream << static_cast<int>(data.playerClass) << ":" << data.playerScore;
  return (stream);
}

std::istream &operator>>(std::istream &stream, PlayerData &data) {
  char tmp;
  int id;

  stream >> id >> tmp >> data.playerScore;
  data.playerClass = static_cast<PlayerId>(id);
  return (stream);
}

// Scoreboard

void Scoreboard::addScore(PlayerId id, int score) {
  scoreboard.emplace_back(id, score);
  sort();
  writeScoreboard(SCOREBOARD_FILE);
}

void Scoreboard::writeScoreboard(std::string const &path) {
  std::ofstream file(path);

  for (auto const &score : scoreboard) {
    file << score << std::endl;
  }
}

void            Scoreboard::loadScoreboard(std::string const &path)
{
  std::ifstream sc(path);
  std::string   buf;

  std::clog << "Loading scoreboard" << std::endl;

  while (std::getline(sc, buf))
  {
    PlayerData pd; // Comme Pedrochu

    sc >> pd;
    std::clog << "Score: " << pd << std::endl;
    scoreboard.emplace_back(pd);
  }
  std::clog << "Finished loading scoreboard" << std::endl;
}

void              Scoreboard::sort()
{
  std::sort(scoreboard.begin(), scoreboard.end(), [](PlayerData const &a, PlayerData const &b){
    return a.playerScore < b.playerScore;
  });
}

std::vector<PlayerData> const &Scoreboard::getScores(void) const {
  return (scoreboard);
}
