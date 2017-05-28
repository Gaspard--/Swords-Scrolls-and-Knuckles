# include <stdexcept>

class AudioError : public std::runtime_error
{
public:
  AudioError(char const *s)
    : std::runtime_error(s)
  {

  }
};
