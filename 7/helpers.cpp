#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "helpers.h"

std::vector<std::string> *read_file(char *file_name) {
  auto results = new std::vector<std::string>();
  auto file = std::ifstream(file_name);

  std::string line;
  while (std::getline(file, line)) {
    results->push_back(line);
  }

  return results;
}

std::string reverse_str(std::string str) {
  if (str.empty()) {
    return str;
  }

  auto result_builder = std::stringstream();
  for (auto i = (int)str.length() - 1; i >= 0; i--) {
    result_builder << str[i];
  }

  return result_builder.str();
}