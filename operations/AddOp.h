#ifndef __PIE_OPERATIONS_ADD_OP_H__
#define __PIE_OPERATIONS_ADD_OP_H__

#include <functional>
#include <vector>
#include <stdexcept>

#include "Operation.h"
#include "../Type.h"
#include "../values/Value.h"
#include "../values/VInt.h"

class AddOp: public Operation {
public:
  AddOp() {
  	f = [](std::vector<Value> args) {
  		if (args.size() != 2) {
  			//TODO: Add to end of string -- but was given" + std::to_string(args.size())
  			throw std::invalid_argument("AddOp requires 2 args");
  		} else {
  			VInt arg1 = *dynamic_cast<VInt*>(&(args[0]));
  			VInt arg2 = *dynamic_cast<VInt*>(&(args[1]));
  			return VInt( arg1.val + arg2.val);
  		}
  	};
  		
  	retType = Type::TInt;
  	argTypes.push_back(Type::TInt);
  	argTypes.push_back(Type::TInt);
  }
};

#endif
