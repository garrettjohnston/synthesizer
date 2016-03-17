#ifndef __PIE_OPERATIONS_GT_OP_H__
#define __PIE_OPERATIONS_GT_OP_H__

#include <functional>
#include <vector>
#include <string>
#include <stdexcept>
#include <boost/any.hpp>

#include "Operation.h"
#include "../Type.h"

class GreaterThanOp: public Operation {
public:
    GreaterThanOp() {
        f = [](std::vector<boost::any> args) {
            if (args.size() != 2) {
                throw std::invalid_argument("GreaterThanOp requires 2 args but was given " + std::to_string(args.size()));
            } else {
                int arg1 = boost::any_cast<int>(args[0]);
                int arg2 = boost::any_cast<int>(args[1]);
                return boost::any(arg1 > arg2);
            }
        };

        retType = Type::TBool;
        argTypes.push_back(Type::TInt);
        argTypes.push_back(Type::TInt);
        isSymmetric = false;
    }

    std::string toString(std::vector<std::tuple<Type, int, int>> args) {
        if (args.size() != 2) {
        return "BAD_GT";
        }
        return "(" + programContainer->get(args[0]).toString() + " > " + programContainer->get(args[1]).toString() + ")";
    }

    std::string name() {
        return "GreaterThanOp";
    }

    bool areGoodArgs(std::vector<std::tuple<Type, int, int>> programs) {
        if (programs.size() != 2) {
            return false;
        }

        Program& program1 = programContainer->get(programs[0]);
        Program& program2 = programContainer->get(programs[1]);
        // Don't allow the same program on both sides of > sign
        // Also don't allow > with only int values, there must be some input value.
        if (program1.id == program2.id || (!program1.containsInputVal && !program2.containsInputVal)) {
            return false;
        }
        // Check for redundancy in child Programs
        if (program1.operation == program2.operation &&
            program1.operation->isRedundant(program1.children, program2.children)) {
            return false;
        }

        return true;
    }

    bool isRedundant(std::vector<std::tuple<Type, int, int>> p1, std::vector<std::tuple<Type, int, int>> p2) {
        return false;
    }
};

#endif
