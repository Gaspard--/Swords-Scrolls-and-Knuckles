#include "Scoreboard.hpp"

// bool operator <(std::vector<PlayerData> a, std::vector<PlayerData> b)
// {
//     return a[0].playerScore < b[0].playerScore;
// }

std::ostream    &operator<<(std::ostream &stream, PlayerData &data)
{
  stream << data.playerName << ":" << data.playerClass << ":" << data.playerScore << " ";
  return (stream);
}

PlayerData::PlayerData(std::string buf)
{
  std::istringstream        strstream(buf);
  std::string               token;

  isScore = true;
  getline(strstream, token, ':');
  playerName = token;
  getline(strstream, token, ':');
  playerClass = token;
  getline(strstream, token, ':');
  playerScore = atoi(token.data());
}

std::vector<PlayerData>     lineToPlayerInfo(std::string buf)
{
    std::istringstream      strstream(buf);
    std::string             token;
    std::vector<PlayerData> data;

    while (getline(strstream, token, ' '))
      data.emplace_back(token);
    return (data);
}

void            Scoreboard::loadDataFromFile(std::string path)
{
  std::ifstream sc;
  std::string   buf;

  sc.open(path);
  if (sc.is_open())
  {
    while (getline(sc, buf))
      scoreboard.emplace_back(lineToPlayerInfo(buf));
  }
  else
    throw std::runtime_error(std::string("Opening Scoreboard file failed: " + path));
}

void            Scoreboard::dumpInfo(std::string path)
{
  std::ofstream sc;

  sc.open(path);
  for (auto &line : scoreboard)
  {
    for (auto &playerData : line)
    {
      if (playerData.isScore)
        sc << playerData;
    }
    sc << std::endl;
  }
}

void              Scoreboard::sort()
{
  std::sort(scoreboard.begin(), scoreboard.end(), [](std::vector<PlayerData> a, std::vector<PlayerData> b){
return a[0].playerScore < b[0].playerScore; });
}

int               main(void)
{
  Scoreboard  board;

  board.loadDataFromFile("scoreboard.scb");
  board.sort();
  board.dumpInfo("sscoreboard.scb");
}
