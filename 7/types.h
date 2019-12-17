#ifndef types_h
#define types_h

#include <map>
#include <vector>

enum Opcode {
  // add
  OP_ADD = 1,

  // mult
  OP_MUL = 2,

  // input & store
  OP_INS = 3,

  // output
  OP_OUT = 4,

  // jump if true
  OP_JIT = 5,

  // jump if false
  OP_JIF = 6,

  // store less than result
  OP_SLT = 7,

  // store eq result
  OP_SEQ = 8,

  // halt
  OP_HLT = 99,
};

enum ParamMode { MODE_POSITION = 0, MODE_IMMEDIATE = 1 };

const int PC_END = -1;

#endif