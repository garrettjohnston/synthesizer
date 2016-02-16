#ifndef __PIE_MULTIPLY_OP_H__
#define __PIE_MULTIPLY_OP_H__

#include <functional>
#include <utility>

#include "Operation.h"
#include "Type.h"

class MultiplyOp: public Operation<int, std::pair<int, int>> {
public:
  MultiplyOp() {
  	f = [](std::pair<int, int> a) { return a.first * a.second; };
  	retType = IntegerT;
  	leftType = IntegerT;
  	rightType = IntegerT;
  }
};

#endif
