#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "helpers.h"
#include "problem_helpers.h"
#include "types.h"

int main(int argc, char** argv) {
  auto file_lines = read_file(argv[1]);
  std::cout << "read " << file_lines->size() << " lines" << std::endl;

  auto graph = build_graph(*file_lines);
  auto num_orbital_transfers = count_orbital_transfers_to(graph, "YOU", "SAN");

  std::cout << "found " << num_orbital_transfers << " orbital transfers" << std::endl;

  std::cout << "done!" << std::endl;
}