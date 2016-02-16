#ifndef __PIE_ADD_OP_H__
#define __PIE_ADD_OP_H__

#include <functional>
#include <utility>

#include "Operation.h"
#include "Type.h"

class AddOp: public Operation<int, std::pair<int, int>> {
public:
  AddOp() {
  	f = [](std::pair<int, int> a) { return a.first + a.second; };
  	retType = IntegerT;
  	leftType = IntegerT;
  	rightType = IntegerT;
  }
};

#endif
