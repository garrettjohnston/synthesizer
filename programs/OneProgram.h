#ifndef __PIE_ONE_PROGRAM_H__
#define __PIE_ONE_PROGRAM_H__

#include <functional>
#include <tuple>

#include "Program.h"
#include "IdentityOp.h"

//template<typename inputTypes...>
class OneProgram: public Program {
public:
  OneProgram() {
  	operation = IdentityOp();
  }
  int evaluate(std::tuple<int> input) {
  	return operation.f(1);
  };
  
};

#endif
