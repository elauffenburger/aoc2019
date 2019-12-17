#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "helpers.h"
#include "vm.h"

const int NUM_AMPS = 5;

const int MIN_PHASE = 0;
const int MAX_PHASE = 4;

int main(int argc, char **argv) {
  auto file_lines = read_file(argv[1]);
  std::cout << "read " << file_lines->size() << " lines" << std::endl;

  auto input = file_lines->at(0);

  auto program_strs = std::vector<std::string>();
  split_str(input, program_strs, ',');

  auto program = map<std::string, int>(
      program_strs, [](std::string ch) { return atoi(ch.c_str()); });

  auto amps = new VM[NUM_AMPS];
  for (auto i = 0; i < NUM_AMPS; i++) {
    amps[i].load(*program);
  }

  auto phases = std::vector<int>();
  for (auto i = MIN_PHASE; i <= MAX_PHASE; i++) {
    phases.push_back(i);
  }

  auto phase_permutations = all_permutations(phases);

  auto max_output = -1;
  auto last_output = 0;

  for (auto phases_it = phase_permutations.begin();
       phases_it != phase_permutations.end(); phases_it++) {
    auto phases = *phases_it;

    try {
      for (auto amp_i = 0; amp_i < NUM_AMPS; amp_i++) {
        auto amp = amps[amp_i];

        amp.push_input(phases[amp_i]);
        amp.push_input(last_output);

        amp.run();

        auto output = amp.pop_output();
        last_output = output;

        if (output > max_output) {
          max_output = output;
        }
      }
    } catch (std::exception e) {
      std::cout << "invalid phase configuration" << std::endl;
    }

    last_output = 0;
  }

  std::cout << "max_output: " << max_output << std::endl;
}