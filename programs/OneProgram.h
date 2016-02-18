#ifndef __PIE_ONE_PROGRAM_H__
#define __PIE_ONE_PROGRAM_H__

#include <functional>
#include <vector>

#include "Program.h"
#include "../operations/IdentityOp.h"

class OneProgram: public Program {
public:
  OneProgram() {
  	operation = IdentityOp();
  }
  Value evaluate(std::vector<Value> input) {
  	std::vector<Value> values;
  	values.push_back(VInt(1));
  	return operation.f(values);
  };
  
};

#endif
