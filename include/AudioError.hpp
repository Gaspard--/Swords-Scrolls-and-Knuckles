#ifndef AUDIOERROR_HPP
# define AUDIOERROR_HPP

# include <stdexcept>

class AudioError : public std::runtime_error
{
public:
  using std::runtime_error::runtime_error;
};

#endif /* !AUDIOERROR_HPP */
