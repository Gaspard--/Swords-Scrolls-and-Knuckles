#include <ios>
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

Scoreboard::Scoreboard(void) {
  loadScoreboard();
  sort();
}

Scoreboard::~Scoreboard(void) {
  writeScoreboard();
}

void Scoreboard::addScore(PlayerId id, int score) {
  scoreboard.emplace_back(id, score);
  sort();
}

void Scoreboard::writeScoreboard(std::string const &path) {
  std::ofstream file(path);

  for (auto const &score : scoreboard) {
    file << score << std::endl;
  }
}

void            Scoreboard::loadScoreboard(std::string const &path)
{
  try {
    std::ifstream sc(path);
    std::string   buf;

    std::clog << "Loading scoreboard" << std::endl;
  
    sc.exceptions(std::ifstream::badbit);
    do
    {
      PlayerData pd; // Comme Pedrochu

      if (!(sc >> pd))
	break;
      std::clog << "Score: " << pd << std::endl;
      if ((int)pd.playerClass >= 0 && (int)pd.playerClass < 4)
	scoreboard.emplace_back(pd);
    } while (std::getline(sc, buf));
  }
  catch (std::ios_base::failure const &) {}

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
