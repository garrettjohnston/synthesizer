#ifndef __PIE_OPERATIONS_LT_OP_H__
#define __PIE_OPERATIONS_LT_OP_H__

#include <functional>
#include <vector>
#include <stdexcept>
#include <string>
#include <boost/any.hpp>

#include "Operation.h"
#include "../Type.h"

class LessThanOp : public Operation {
public:
    LessThanOp() {
        f = [](std::vector<boost::any> args) {
            if (args.size() != 2) {
                throw std::invalid_argument("LessThanOp requires 2 args but was given " + std::to_string(args.size()));
            } else {
                int arg1 = boost::any_cast<int>(args[0]);
                int arg2 = boost::any_cast<int>(args[1]);
                return boost::any(arg1 < arg2);
            }
        };
        retType = Type::TBool;
        argTypes.push_back(Type::TInt);
        argTypes.push_back(Type::TInt);
        isSymmetric = false;
        isComposable = true;
    }

    std::string toString(std::vector<std::tuple<Type, int, int>> args) {
        if (args.size() != 2) {
            return "BAD_LT";
        }
        return "(" + programContainer->get(args[0]).toString() + " < " + programContainer->get(args[1]).toString() + ")";
    }

    std::string name() {
        return "LessThanOp";
    }

    bool areGoodArgs(std::vector<std::tuple<Type, int, int>> program) {
        return true;
    }
//
//    bool isGoodArg(std::tuple<Type, int, int> p1, std::tuple<Type, int, int> p2) {
//        Program& program1 = programContainer->get(p1);
//        Program& program2 = programContainer->get(p2);
//        // Don't allow the same program on both sides of < sign
//        if (p1 == p2) {
//            return false;
//        }
//        // Check for redundancy in child Programs
//        if (program1.operation == program2.operation &&
//            program1.operation->isRedundant(program1.children, program2.children)) {
//            return false;
//        }
//
//        return true;
//    }

    bool isRedundant(std::vector<std::tuple<Type, int, int>> p1, std::vector<std::tuple<Type, int, int>> p2) {
        return false;
    }
};

#endif
