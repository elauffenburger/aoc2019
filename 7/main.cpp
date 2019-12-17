#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "helpers.h"
#include "vm.h"

int main(int argc, char **argv) {
  auto file_lines = read_file(argv[1]);
  std::cout << "read " << file_lines->size() << " lines" << std::endl;

  auto input = file_lines->at(0);

  auto program_strs = std::vector<std::string>();
  split_str(input, program_strs, ',');

  auto program = map<std::string, int>(
      program_strs, [](std::string ch) { return atoi(ch.c_str()); });

  auto vm = VM(atoi(argv[2]));
  vm.load(*program);
  vm.run();
}