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
  SelectorOp() {
  	f = [](std::vector<Value> args) { 
  		if (args.size() != 1) {
  			//TODO: Add to end of string -- but was given" + std::to_string(args.size())
  			throw std::invalid_argument("SelectorOp requires 1 arg");
  		} else {
  			VInt arg1 = *dynamic_cast<VInt*>(&(args[0]));
  			return VInt(42); // TODO: actually implement this
  		}
  	};
  		
  	retType = Type::TInt;
  	argTypes.push_back(Type::TInt);
  }
};

#endif
