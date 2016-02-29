#ifndef __PIE_OPERATIONS_GT_OP_H__
#define __PIE_OPERATIONS_GT_OP_H__

#include <functional>
#include <vector>
#include <string>
#include <stdexcept>
#include <boost/any.hpp>

#include "Operation.h"
#include "../Type.h"
#include "../values/Value.h"

class GreaterThanOp: public Operation {
public:
  GreaterThanOp() {
  	f = [](std::vector<Value> args) {
  		if (args.size() != 2) {
  			throw std::invalid_argument("GreaterThanOp requires 2 args but was given " + std::to_string(args.size()));
  		} else {
        int arg1 = boost::any_cast<int>(args[0]);
        int arg2 = boost::any_cast<int>(args[1]);
        return Value(arg1 > arg2);
  		}
  	};
  		
  	retType = Type::TBool;
  	argTypes.push_back(Type::TInt);
  	argTypes.push_back(Type::TInt);
  }

	std::string toString(std::vector<std::tuple<Type, int, int>> args) {
		if (args.size() != 2) {
			return "BAD_GT";
		}

		return "(" + programContainer->get(args[0]).toString() + " > " + programContainer->get(args[1]).toString() + ")";
	}
};

#endif
