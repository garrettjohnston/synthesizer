#ifndef __PIE_OPERATIONS_ADD_OP_H__
#define __PIE_OPERATIONS_ADD_OP_H__

#include <functional>
#include <vector>
#include <string>
#include <stdexcept>
#include <boost/any.hpp>
#include <typeinfo>

#include "Operation.h"
#include "IdentityOp.h"
#include "../Type.h"

class AddOp: public Operation {
public:
	AddOp() {
		f = [](std::vector<boost::any> args) {
			if (args.size() != 2) {
				throw std::invalid_argument("AddOp requires 2 args but was given " + std::to_string(args.size()));
			} else {
			int arg1 = boost::any_cast<int>(args[0]);
			int arg2 = boost::any_cast<int>(args[1]);
				return boost::any(arg1 + arg2);
			}
		};
  		
		retType = Type::TInt;
		argTypes.push_back(Type::TInt);
		argTypes.push_back(Type::TInt);
        isSymmetric = true;
        isComposable = true;
	}

	std::string toString(std::vector<std::tuple<Type, int, int>> args) {
		if (args.size() != 2) {
			return "BAD_ADD";
		}
        return "(" + programContainer->get(args[0]).toString() + " + " + programContainer->get(args[1]).toString() + ")";
	}

    std::string name() {
        return "AddOp";
    }

    // Returns false if a 0 Program is found. Else true.
	bool isGoodArg(std::tuple<Type, int, int> p) {
        Program& program = programContainer->get(p);
        IdentityOp* b = dynamic_cast<IdentityOp*>(program.operation);
        if (b != NULL) {
            IdentityOp* op = (IdentityOp*) program.operation;
            int i = boost::any_cast<int>(op->val);
            if (i == 0) {
                return false;
            }
        }

        return true;
	}

    // TODO: Could expand this further if we introduce negative/subtract operator.
    bool isGoodArg(std::tuple<Type, int, int> p1, std::tuple<Type, int, int> p2) {
        return isGoodArg(p1) && isGoodArg(p2);
    }

    // Check ONE level deep for redundant expressions. e.g. (i+1) == (1+1) is equiv to i == 1
    bool isRedundant(std::vector<std::tuple<Type, int, int>> p1, std::vector<std::tuple<Type, int, int>> p2) {
        for (auto expr1 : p1) {
            for (auto expr2 : p2) {
                if (expr1 == expr2)
                    return true;
            }
        }
        return false;
    }
};

#endif
