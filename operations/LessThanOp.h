#ifndef __PIE_LT_OP_H__
#define __PIE_LT_OP_H__

#include <functional>
#include <utility>

#include "Operation.h"
#include "Type.h"

class LessThanOp: public Operation<int, std::pair<int, int>> {
public:
  LessThanOp() {
  	f = [](std::pair<int, int> a) { return a.first < a.second; };
  	retType = BooleanT;
  	leftType = IntegerT;
  	rightType = IntegerT;
  }
};

#endif
