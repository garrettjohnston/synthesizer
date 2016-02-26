#ifndef __PIE_OPERATIONS_IDENTITY_OP_H__
#define __PIE_OPERATIONS_IDENTITY_OP_H__

#include <functional>
#include <vector>
#include <stdexcept>

#include "Operation.h"
#include "../Type.h"
#include "../values/Value.h"
#include "../values/VInt.h"

// TODO: Do I need an Int identity and Bool and Str identity? Or can I generalize this.
class IdentityOp: public Operation {
public:
  IdentityOp() {
  	f = [](std::vector<Value> args) {
  		if (args.size() != 1) {
  			throw std::invalid_argument("IdentityOp requires 1 arg but was given " + std::to_string(args.size()));
  		} else {
  			return args[0];
  		}
  	};
  		
  	retType = Type::TInt;
  	argTypes.push_back(Type::TInt);
  }
};

#endif
