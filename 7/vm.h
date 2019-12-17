#ifndef vm_h
#define vm_h

#include <vector>
#include <optional>

#include "instr.h"

class VM {
 public:
  int pc;
  std::vector<int> program;

  VM(int input_val) : input_val(input_val) {}

  void load(std::vector<int> program);

  int read(int addr) const;
  void write(int addr, int value);

  int get_input();
  void output(int value);

  ProgramOp* get_op_from_opcode(int opcode);
  ProgramInstr* decode_instr(int instr_prefix, std::vector<int> program);

  void run();

 private:
  int input_val;
  std::optional<Opcode> expected_opcode;
};

#endif