#ifndef __PIE_GT_OP_H__
#define __PIE_GT_OP_H__

#include <functional>
#include <utility>

#include "Operation.h"
#include "Type.h"

class GreaterThanOp: public Operation<int, std::pair<int, int>> {
public:
  GreaterThanOp() {
  	f = [](std::pair<int, int> a) { return a.first > a.second; };
  	retType = BooleanT;
  	leftType = IntegerT;
  	rightType = IntegerT;
  }
};

#endif
