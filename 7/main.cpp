#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "helpers.h"
#include "vm.h"

const int NUM_AMPS = 5;

const int MIN_PHASE = 5;
const int MAX_PHASE = 9;

std::vector<int>* read_program_from_file(char* filename) {
  auto file_lines = read_file(filename);
  std::cout << "read " << file_lines->size() << " lines" << std::endl;

  auto input = file_lines->at(0);

  auto program_strs = std::vector<std::string>();
  split_str(input, program_strs, ',');

  auto program = map<std::string, int>(
      program_strs, [](std::string ch) { return atoi(ch.c_str()); });

  return program;
}

std::vector<std::vector<int>> build_phase_permutations(int min_phase,
                                                       int max_phase) {
  auto phases = std::vector<int>();
  for (auto i = min_phase; i <= max_phase; i++) {
    phases.push_back(i);
  }

  return all_permutations(phases);
}

std::vector<VM> build_amps(std::vector<int>* program, bool wire_feedback_loop) {
  auto amps = std::vector<VM>();

  for (auto i = 0; i < NUM_AMPS; i++) {
    amps.push_back(VM("vm " + to_str(i + 1)));

    auto next_amp_i = i == NUM_AMPS - 1 ? 0 : i + 1;
    auto previous_amp_i = i == 0 ? NUM_AMPS - 1 : i - 1;

    amps[i].output_writer = [&, next_amp_i](int output) {
      amps[next_amp_i].push_input(output);
      amps[next_amp_i].run(true);
    };
  }

  return amps;
}

void print_phases(const std::vector<int>& phases) {
  for (auto it = phases.begin(); it != phases.end(); it++) {
    std::cout << *it << " ";
  }

  std::cout << std::endl;
}

int main(int argc, char** argv) {
  auto program = read_program_from_file(argv[1]);
  auto amps = build_amps(program, argc > 2 && argv[2] == "true");
  auto phase_permutations =
      build_phase_permutations(argc > 3 ? atoi(argv[3]) : MIN_PHASE,
                               argc > 4 ? atoi(argv[4]) : MAX_PHASE);

  auto max_output = -1;

  for (auto phases_it = phase_permutations.begin();
       phases_it != phase_permutations.end(); phases_it++) {
    auto phases = *phases_it;

    try {
#ifdef DEBUG
      print_phases(phases);
#endif

      // init amps
      for (auto amp_i = 0; amp_i < NUM_AMPS; amp_i++) {
        amps[amp_i].load(*program);
        amps[amp_i].reset();
        amps[amp_i].push_input(phases[amp_i]);
      }

      amps[0].push_input(0);
      amps[0].run(true);

      auto output = amps[NUM_AMPS - 1].peek_last_output();
      if (output > max_output) {
        max_output = output;
      }
    } catch (std::exception e) {
      std::cout << "bad phase configuration" << std::endl;
    }
  }

  std::cout << "max_output: " << max_output << std::endl;
}