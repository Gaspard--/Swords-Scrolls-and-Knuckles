#ifndef MOD_VECTOR
# define MOD_VECTOR

#include <vector>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <functional>

#include "Util.hpp"

/**
 * A class that copies modifications from one std::vector to another
 * Slightly unoptimised (but it probably won't be a performance critical part)
 */
template<class T, class U>
class ModVector
{
private:
  std::vector<T> &modified;
  std::vector<U> &target;

  struct Mod
  {
    std::vector<std::function<U(void)>> additions;
    unsigned int removalStart;
    std::vector<std::pair<unsigned int, unsigned int>> removals;
  };

  std::vector<Mod> mods;

public:
  ModVector(std::vector<T> &modified,
		      std::vector<U> &target)
    : modified(modified)
    , target(target)
    , mods()
  {
    mods.emplace_back();
  }

  template<class... PARAMS>
  void add(std::function<U(void)> func, PARAMS &&... params)
  {
    mods.back().additions.push_back(func);
    modified.emplace_back(std::forward<PARAMS>(params)...);
  }

  void updateTarget()
  {
    for (Mod const &mod : mods)
      {
	for (auto &&addition : mod.additions)
	  target.push_back(addition());

	if (!mod.removals.empty())
	  {
	    auto write(target.begin() + mod.removalStart);
	    auto read(write);

	    for (auto &&moved : mod.removals)
	      {
		auto const rangeBegin(read + moved.first);
		auto const rangeEnd(read + moved.second);

		write = std::move(rangeBegin, rangeEnd, write);
		read = rangeEnd;
	      }
	    target.resize(write - target.begin());
	  }
      }
    mods.clear();
    mods.emplace_back();
  }

  template<class PREDICATE>
  void removeIf(PREDICATE p)
  {
    auto write(std::find_if(modified.begin(), modified.end(), p));
    auto read(write);

    mods.back().removalStart = write - modified.begin();
    while (read != modified.end())
      {
	auto const rangeBegin(std::find_if(read, modified.end(), makeNot(p)));
	auto const rangeEnd(std::find_if(rangeBegin, modified.end(), p));

	mods.back().removals.emplace_back(rangeBegin - read, rangeEnd - read);
	write = std::move(rangeBegin, rangeEnd, write);
	read = rangeEnd;
      }
    modified.resize(write - modified.begin());
    mods.emplace_back();
  }

  template<class Func>
  void forEach(Func func)
  {
    auto modifiedIt(modified.begin());
    auto targetIt(target.begin());

    while (modifiedIt != modified.end())
      {
	func(*targetIt, *modifiedIt);
	++modifiedIt;
	++targetIt;
      }
    if (targetIt != target.end())
      {
	std::clog << "[ModVect] Fatal error occured:" << std::endl;
	std::clog << "[ModVect] ModVect::forEach called at invalid moment." << std::endl;
	std::clog << "[ModVect] (target size, modified size) : " << target.size() << ", " << modified.size() << std::endl;
        throw std::logic_error("ModVect::forEach called at invalid moment.");
      }
  }
};

#endif
