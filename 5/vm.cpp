#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "helpers.h"
#include "types.h"
#include "vm.h"

class UnknownOpcodeException : public std::exception {
  virtual const char* what() const throw() { return "Unknown opcode"; }
};

class InvalidOutputException : public std::exception {};

void VM::load(std::vector<int> program) {
  this->program = program;
  this->pc = 0;
}

int VM::read(int addr) const { return this->program.at(addr); }
void VM::write(int addr, int value) { this->program.at(addr) = value; }

int VM::get_input() {
  return this->output_val;
}

void VM::output(int value) {
  std::cout << "output: " << value << std::endl;

  auto next_instr = this->decode_instr(this->read(this->pc + 2), this->program);
  if (next_instr->op->opcode == OP_HLT) {
    return;
  }

  if (value != 0) {
    throw InvalidOutputException();
  }
}

ProgramOp* VM::get_op_from_opcode(int opcode) {
  switch (opcode) {
    case OP_ADD:
      return new AddProgramOp();
    case OP_MUL:
      return new MulProgramOp();
    case OP_INS:
      return new InsProgramOp();
    case OP_OUT:
      return new OutProgramOp();
    case OP_JIT:
      return new JitProgramOp();
    case OP_JIF:
      return new JifProgramOp();
    case OP_SLT:
      return new SltProgramOp();
    case OP_SEQ:
      return new SeqProgramOp();
    case OP_HLT:
      return new HltProgramOp();
    default:
      throw UnknownOpcodeException();
  }
}

ProgramInstr* VM::decode_instr(int instr_prefix, std::vector<int> program) {
  auto instr_prefix_str = to_str(instr_prefix);

  std::string instr_parts[2] = {};
  if (instr_prefix_str.length() <= 2) {
    instr_parts[0] = instr_prefix_str.substr(instr_prefix_str.length() - 1);
    instr_parts[1] = std::string("");
  } else {
    instr_parts[0] = instr_prefix_str.substr(2, instr_prefix_str.length() - 2);
    instr_parts[1] = instr_prefix_str.substr(0, instr_prefix_str.length() - 2);
  }

  // Get opcode.
  auto opcode = atoi(instr_parts[0].c_str());
  auto op = get_op_from_opcode(opcode);

  // Get known param modes.
  auto param_modes = map<char, ParamMode>(
      to_vec<char>(reverse_str(instr_parts[1])),
      [](char digit) -> ParamMode { return (ParamMode)atoi(&digit); });

  // Pad the unlisted param_modes with the default mode.
  for (auto i = param_modes->size(); i < op->get_num_params(); i++) {
    param_modes->push_back(MODE_POSITION);
  }

  return new ProgramInstr{.op = op, .param_modes = *param_modes};
}

void VM::run() {
  while (pc != PC_END) {
    auto instr_prefix = this->read(pc);
    auto instr = decode_instr(instr_prefix, program);

    instr->exec(*this);
  }
}