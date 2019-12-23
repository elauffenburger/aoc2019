#include <exception>
#include <vector>

#include "instr.h"
#include "vm.h"

class OverflowException : std::exception {};

void ProgramInstr::exec(VM& vm) {
#ifdef DEBUG
  printf("%s: %d\n", vm.name.c_str(), this->op->opcode);
#endif

  this->op->exec(vm, this->param_modes);
}

int ProgramOp::resolve_param_value(int pc, ParamMode mode, const VM& vm) {
  auto param = vm.read(pc);

  return mode == MODE_IMMEDIATE ? param : vm.read(param);
}

void AddProgramOp::exec(VM& vm, const std::vector<ParamMode>& param_modes) {
  auto param1 = this->resolve_param_value(vm.pc + 1, param_modes.at(0), vm);
  auto param2 = this->resolve_param_value(vm.pc + 2, param_modes.at(1), vm);

  auto result_addr = vm.read(vm.pc + 3);
  auto result = param1 + param2;

  if (result < 0) {
    throw std::exception();
  }

  vm.write(result_addr, result);

  vm.pc += 4;
}

void MulProgramOp::exec(VM& vm, const std::vector<ParamMode>& param_modes) {
  auto param1 = this->resolve_param_value(vm.pc + 1, param_modes.at(0), vm);
  auto param2 = this->resolve_param_value(vm.pc + 2, param_modes.at(1), vm);

  auto result_addr = vm.read(vm.pc + 3);

  vm.write(result_addr, param1 * param2);

  vm.pc += 4;
}

void InsProgramOp::exec(VM& vm, const std::vector<ParamMode>& param_modes) {
  auto input = vm.read_input();
  auto result_addr = vm.read(vm.pc + 1);

  vm.write(result_addr, input);

  vm.pc += 2;
}

void OutProgramOp::exec(VM& vm, const std::vector<ParamMode>& param_modes) {
  auto param = this->resolve_param_value(vm.pc + 1, param_modes.at(0), vm);

  vm.pc += 2;

  vm.write_output(param);
}

void JitProgramOp::exec(VM& vm, const std::vector<ParamMode>& param_modes) {
  auto param1 = this->resolve_param_value(vm.pc + 1, param_modes.at(0), vm);
  auto param2 = this->resolve_param_value(vm.pc + 2, param_modes.at(1), vm);

  if (param1 != 0) {
    vm.pc = param2;
  } else {
    vm.pc += 3;
  }
}

void JifProgramOp::exec(VM& vm, const std::vector<ParamMode>& param_modes) {
  auto param1 = this->resolve_param_value(vm.pc + 1, param_modes.at(0), vm);
  auto param2 = this->resolve_param_value(vm.pc + 2, param_modes.at(1), vm);

  if (param1 == 0) {
    vm.pc = param2;
  } else {
    vm.pc += 3;
  }
}

void SltProgramOp::exec(VM& vm, const std::vector<ParamMode>& param_modes) {
  auto param1 = this->resolve_param_value(vm.pc + 1, param_modes.at(0), vm);
  auto param2 = this->resolve_param_value(vm.pc + 2, param_modes.at(1), vm);

  auto result_addr = vm.read(vm.pc + 3);

  vm.write(result_addr, param1 < param2 ? 1 : 0);

  vm.pc += 4;
}

void SeqProgramOp::exec(VM& vm, const std::vector<ParamMode>& param_modes) {
  auto param1 = this->resolve_param_value(vm.pc + 1, param_modes.at(0), vm);
  auto param2 = this->resolve_param_value(vm.pc + 2, param_modes.at(1), vm);

  auto result_addr = vm.read(vm.pc + 3);

  vm.write(result_addr, param1 == param2 ? 1 : 0);

  vm.pc += 4;
}

void HltProgramOp::exec(VM& vm, const std::vector<ParamMode>& param_modes) {
  vm.pc = PC_END;
}