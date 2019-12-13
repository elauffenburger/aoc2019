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

void print_wire_instrs(const std::vector<WireInstr> &instrs) {
  for (auto it = instrs.begin(); it != instrs.end(); it++) {
    auto instr = *it;

    std::cout << (char)instr.direction << instr.value << std::endl;
  }
}

int main(int argc, char **argv) {
  auto file_lines = read_file(argv[1]);
  std::cout << "read " << file_lines->size() << " lines" << std::endl;

  std::vector<WireInstr> wires[2] = {parse_wire_instrs(file_lines->at(0)),
                                     parse_wire_instrs(file_lines->at(1))};

  auto grid = init_grid();
  auto track_list = Tracklist();
  auto central_port = Point{.x = 1, .y = 1};

  // Trace wire 1
  draw_wire(*grid, track_list, central_port,
            WireContext{.number = 1, .instrs = wires[0]}, false);

  // Trace wire 2
  draw_wire(*grid, track_list, central_port,
            WireContext{.number = 2, .instrs = wires[1]}, true);

  // Find closest manhattan distance intersection
  Intersection *closest_intersection = nullptr;
  int closest_intersection_distance = -1;
  for (auto it = track_list.begin(); it != track_list.end(); it++) {
    auto distance = (*it).marks[0].num_steps + (*it).marks[1].num_steps;

    if (closest_intersection == nullptr ||
        distance < closest_intersection_distance) {
      closest_intersection_distance = distance;
      closest_intersection = &(*it);
      continue;
    }
  }

  if (closest_intersection == nullptr) {
    std::cout << "no match found :(" << std::endl;

    exit(1);
  }

  std::cout << "closest point: (" << closest_intersection->point.x << ","
            << closest_intersection->point.y
            << ") w/ distance: " << closest_intersection_distance << std::endl;
}