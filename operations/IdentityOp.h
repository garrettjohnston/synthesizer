#ifndef __PIE_IDENTITY_OP_H__
#define __PIE_IDENTITY_OP_H__

#include <functional>

#include "Operation.h"
#include "Type.h"

class IdentityOp: public Operation<int, int> {
public:  
  IdentityOp() {
  	f = [](int a) { return a; };
  	// TODO: pass in Type as argument to constructor, based on "input" type
  	retType = IntegerT;
  	leftType = IntegerT;
  	rightType = IntegerT;
  }
};

#endif
