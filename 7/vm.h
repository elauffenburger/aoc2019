#ifndef vm_h
#define vm_h

#include <optional>
#include <queue>
#include <vector>

#include "instr.h"

class VM {
 public:
  int pc;
  std::vector<int> program;

  VM() {
    inputs = std::queue<int>();
    outputs = std::queue<int>();
  }

  void load(std::vector<int> program);

  void push_input(int input);
  int pop_output();

  int read(int addr) const;
  void write(int addr, int value);

  int read_input();
  void write_output(int value);

  ProgramOp* get_op_from_opcode(int opcode);
  ProgramInstr* decode_instr(int instr_prefix, std::vector<int> program);

  void run();

 private:
  std::queue<int> inputs;
  std::queue<int> outputs;

  std::optional<Opcode> expected_opcode;
};

#endif