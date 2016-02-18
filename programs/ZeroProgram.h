#ifndef __PIE_ZERO_PROGRAM_H__
#define __PIE_ZERO_PROGRAM_H__

#include <functional>
#include <tuple>

#include "Program.h"
#include "../operations/IdentityOp.h"
#include "../values/Value.h"

class ZeroProgram: public Program {
public:
  ZeroProgram() {
  	operation = IdentityOp();
  }
  Value evaluate(std::vector<Value> input) {
  	std::vector<Value> values;
  	values.push_back(VInt(0));
  	return operation.f(values);
  };
  
};

#endif
