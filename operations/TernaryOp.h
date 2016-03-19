#ifndef SYNTHESIZER_TERNARYOP_H
#define SYNTHESIZER_TERNARYOP_H

#include <functional>
#include <vector>
#include <string>
#include <stdexcept>
#include <boost/any.hpp>
#include <typeinfo>

#include "Operation.h"
#include "primitive/IdentityOp.h"
#include "../Type.h"
#include "../programs/Program.h"

class TernaryOp: public Operation {
public:
    TernaryOp() {
        f = [](std::vector<boost::any> args) {
            if (args.size() != 3) {
                throw std::invalid_argument("TernaryOp requires 3 args but was given " + std::to_string(args.size()));
            } else {
                bool arg1 = boost::any_cast<bool>(args[0]);
                int arg2 = boost::any_cast<int>(args[1]);
                int arg3 = boost::any_cast<int>(args[2]);
                return boost::any(arg1 ? arg2 : arg3);
            }
        };

        retType = Type::TInt;
        argTypes.push_back(Type::TBool);
        argTypes.push_back(Type::TInt);
        argTypes.push_back(Type::TInt);
        isSymmetric = false;
    }

    std::string toString(std::vector<std::tuple<Type, int, int>> args) {
        if (args.size() != 3) {
            return "BAD_ADD";
        }
        return "(" + programContainer->get(args[0]).toString()
               + " ? " + programContainer->get(args[1]).toString()
               + " : " + programContainer->get(args[2]).toString() + ")";
    }

    std::string name() {
        return "TernaryOp";
    }

    bool areGoodArgs(std::vector<std::tuple<Type, int, int>> programs) {
        if (programs.size() != 3) {
            return false;
        }

        // If bool value is just true or false, then this function is useless
        // If int programs are the same, then this function is useless
        Program &boolProgram = programContainer->get(programs[0]);
        Program &intProgram1 = programContainer->get(programs[1]);
        Program &intProgram2 = programContainer->get(programs[2]);
        if (!boolProgram.containsInputVal || intProgram1.id == intProgram2.id) {
            return false;
        }

        return true;
    }

    bool isRedundant(std::vector<std::tuple<Type, int, int>> p1, std::vector<std::tuple<Type, int, int>> p2) {
        return false;
    }
};

#endif
