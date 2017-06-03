#include "Scoreboard.hpp"

std::ostream    &operator<<(std::ostream &stream, PlayerData const &data)
{
  stream << data.playerName << ":" << data.playerClass << ":" << data.playerScore << " ";
  return (stream);
}

PlayerData::PlayerData(std::string buf)
{
  std::istringstream        strstream(buf);
  std::string               token;

  try
  {
    std::getline(strstream, token, ':');
    playerName = token;
    std::getline(strstream, token, ':');
    playerClass = token;
    std::getline(strstream, token, ':');
    playerScore = stoi(token);
  }
  catch (std::runtime_error)
  {
    throw std::runtime_error(std::string("Reading Scoreboard file failed"));
  }
  isScore = true;
}

std::vector<PlayerData>     lineToPlayerInfo(std::string buf)
{
    std::istringstream      strstream(buf);
    std::string             token;
    std::vector<PlayerData> data;

    while (std::getline(strstream, token, ' '))
      data.emplace_back(token);
    return (data);
}

void            Scoreboard::loadDataFromFile(std::string path)
{
  std::ifstream sc;
  std::string   buf;

  sc.open(path);
  if (!sc.is_open())
    throw std::runtime_error(std::string("Opening Scoreboard file failed: " + path));
  while (std::getline(sc, buf))
    scoreboard.emplace_back(lineToPlayerInfo(buf));
}

void            Scoreboard::dumpInfo(std::string path)
{
  std::ofstream sc;

  sc.open(path);
  sort();
  for (auto const &line : scoreboard)
  {
    for (auto const &playerData : line)
    {
      if (playerData.isScore)
        sc << playerData;
    }
    sc << std::endl;
  }
}

void              Scoreboard::sort()
{
  std::sort(scoreboard.begin(), scoreboard.end(), [](std::vector<PlayerData> const &a, std::vector<PlayerData> const &b){
return a[0].playerScore < b[0].playerScore; });
}
