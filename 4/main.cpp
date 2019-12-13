#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "helpers.h"
#include "problem_helpers.h"
#include "types.h"

int main(int argc, char **argv) {
  auto file_lines = read_file(argv[1]);
  std::cout << "read " << file_lines->size() << " lines" << std::endl;

  auto input_parts = std::vector<std::string>();
  split_str(file_lines->at(0), input_parts, '-');

  std::cout << "split input into " << input_parts.size() << " parts"
            << std::endl;

  int range[2] = {atoi(input_parts.at(0).c_str()),
                  atoi(input_parts.at(1).c_str())};

  std::cout << "range: " << range[0] << " to " << range[1] << std::endl;

  auto passwords = std::vector<int>();
  compute_passwords(range[0], range[1], passwords);

#ifdef DEBUG
  for (auto it = passwords.begin(); it != passwords.end(); it++) {
    std::cout << *it << std::endl;
  }
#endif

  std::cout << "Found " << passwords.size() << " passwords" << std::endl;
}