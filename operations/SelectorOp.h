#ifndef __PIE_OPERATIONS_SELECTOR_OP_H__
#define __PIE_OPERATIONS_SELECTOR_OP_H__

#include <functional>
#include <vector>
#include <stdexcept>

#include "Operation.h"
#include "../Type.h"
#include "../values/Value.h"
#include "../values/VInt.h"

class SelectorOp: public Operation {
public:
  SelectorOp(int index) {
    // Function takes as input, the vector of input values, followed by an index of which one to return
  	f = [index](std::vector<Value> args) {
      return args.at(index); //TODO Fix this
  	};
  		
  	retType = Type::TStr; // Shouldn't really need any types here, as we never refer to this operator except at level 0
  	argTypes.push_back(Type::TStr);
  }
};

#endif