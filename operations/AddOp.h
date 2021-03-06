#ifndef __PIE_OPERATIONS_ADD_OP_H__
#define __PIE_OPERATIONS_ADD_OP_H__

#include <functional>
#include <vector>
#include <string>
#include <stdexcept>
#include <boost/any.hpp>
#include <typeinfo>

#include "Operation.h"
#include "primitive/IdentityOp.h"
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
	bool areGoodArgs(std::vector<std::tuple<Type, int, int>> programs) {
		if (programs.size() != 2) {
            return false;
        }

        for (int i = 0; i < 2; i++) {
            Program &program = programContainer->get(programs[i]);
            IdentityOp *op = dynamic_cast<IdentityOp *>(program.operation);
            if (op != NULL) {
                int i = boost::any_cast<int>(op->val);
                if (i == 0) {
                    return false;
                }
            }
        }

        return true;
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
