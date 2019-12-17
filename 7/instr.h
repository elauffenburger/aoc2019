#ifndef instr_h
#define instr_h

#include <vector>

#include "types.h"

class VM;

#define NEW_OP(NAME, OPCODE, NUM_PARAMS) \
    class NAME : public virtual ProgramOp{ \
        \
        public: \
        \
        NAME() { this->opcode = OPCODE; } \
        \
        virtual void exec(VM& vm, const std::vector<ParamMode>& param_modes); \
        \
        int get_num_params() { return NUM_PARAMS; } \
    }; 

class ProgramOp {
 public:
  Opcode opcode;

  virtual void exec(VM& program, const std::vector<ParamMode>& param_modes) = 0;
  virtual int get_num_params() = 0;

 protected:
  int resolve_param_value(int param, ParamMode mode, const VM& vm);
};

NEW_OP(AddProgramOp, OP_ADD, 2)
NEW_OP(MulProgramOp, OP_MUL, 2)
NEW_OP(InsProgramOp, OP_INS, 2)
NEW_OP(OutProgramOp, OP_OUT, 1)
NEW_OP(JitProgramOp, OP_JIT, 2)
NEW_OP(JifProgramOp, OP_JIF, 2)
NEW_OP(SltProgramOp, OP_SLT, 3)
NEW_OP(SeqProgramOp, OP_SEQ, 3)
NEW_OP(HltProgramOp, OP_HLT, 0)

class ProgramInstr {
 public:
  ProgramOp* op;
  std::vector<ParamMode> param_modes;

  void exec(VM& vm);
};

#endif