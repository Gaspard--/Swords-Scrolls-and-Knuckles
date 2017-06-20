#ifndef OPTIONS_HPP
# define OPTIOSN_HPP

# include <functional>
# include <string>

class Option
{
  bool activated;
  std::string name;
  std::function<void(bool)> callback;

public:
  Option(void) = delete;
  Option(std::string const &name, bool, std::function<void(bool)> const &l);
  Option(Option const &) = default;
  Option(Option &&) = default;
  Option &operator=(Option const &) = default;
  Option &operator=(Option &&) = default;
  ~Option(void) = default;

  bool isActivated(void) const;
  void setOption(bool b);
  std::string const &getName(void) const;
};

#endif // !OPTIONS_HPP
