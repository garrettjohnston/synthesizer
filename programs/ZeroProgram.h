#ifndef __PIE_ZERO_PROGRAM_H__
#define __PIE_ZERO_PROGRAM_H__

#include <functional>
#include <tuple>

#include "Program.h"
#include "IdentityOp.h"

//template<typename inputTypes...>
class ZeroProgram: public Program {
public:
  ZeroProgram() {
  	operation = IdentityOp();
  }
  int evaluate(std::tuple<int> input) {
  	return operation.f(0);
  };
  
};

#endif
