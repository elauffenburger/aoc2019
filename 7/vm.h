#ifndef vm_h
#define vm_h

#include <functional>
#include <optional>
#include <queue>
#include <vector>

#include "instr.h"

class VM {
 public:
  int pc;
  std::string name;
  std::vector<int> program;
  std::function<void(int)> output_writer;
  std::function<int()> input_reader;

  VM(std::string name) : name(name) {
    pc = 0;
    inputs = std::queue<int>();
    outputs = std::queue<int>();
    output_writer = [](int output) {};
  }

  void load(std::vector<int> program);

  void push_input(int input);
  int pop_output();
  int peek_last_output();

  int read(int addr) const;
  void write(int addr, int value);

  int read_input();
  void write_output(int value);

  ProgramOp* get_op_from_opcode(int opcode);
  ProgramInstr* decode_instr(int instr_prefix, std::vector<int> program);

  void reset();
  void run(bool run_to_output);

 private:
  std::queue<int> inputs;
  std::queue<int> outputs;

  std::optional<Opcode> expected_opcode;
};

#endif