#ifndef vm_h
#define vm_h

#include <vector>

#include "instr.h"

class VM {
 public:
  int pc;
  std::vector<int> program;

  VM(int output_val) : output_val(output_val) {}

  void load(std::vector<int> program);

  int read(int addr) const;
  void write(int addr, int value);

  int get_input();
  void output(int value);

  ProgramOp* get_op_from_opcode(int opcode);
  ProgramInstr* decode_instr(int instr_prefix, std::vector<int> program);

  void run();

 private:
  int output_val;
};

#endif