#include "main.hpp"

int main() {
  // Ensure that we are compiling with C++14.
  // TODO : remove as soon as we have something else to put here.
  auto print = [](auto i) {
    std::cout << i << std::endl;
  };

  print("Hello Ogre World !");
  return (0);
}
