//
// main.cpp for  in /home/grange_c/rendu/indie/source
//
// Made by Benjamin Grange
// Login   <grange_c@epitech.net>
//
// Started on  Tue May 09 23:25:02 2017 Benjamin Grange
// Last update Tue May 09 23:25:02 2017 Benjamin Grange
//

#include "main.hpp"

int main() {
  // Ensure that we are compiling with C++14.
  // TODO : remove as soon as we have something else to put here.
  auto print = [](auto i) {
    std::cout << i << std::endl;
  };

  print("Hello Gnome World !");
  return (0);
}
