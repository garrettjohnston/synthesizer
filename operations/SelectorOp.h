#ifndef __PIE_OPERATIONS_SELECTOR_OP_H__
#define __PIE_OPERATIONS_SELECTOR_OP_H__

#include <functional>
#include <vector>
#include <stdexcept>
#include <string>

#include "Operation.h"
#include "../Type.h"
#include "../values/Value.h"

class SelectorOp : public Operation {
public:
    int index;

    SelectorOp(int i, Type type) { // TODO: Maybe don't pass in Type explicitly, but figure it out from args
        // Function takes as input, the vector of input values
        index = i;
        f = [this](std::vector<Value> args) {
            return args.at(this->index);
        };

        retType = type;
        argTypes.push_back(Type::TStr); // argTypes should never really be called for this op
    }

    std::string toString(std::vector<std::tuple<Type, int, int>> args) {
        if (args.size() != 0) {
            return "BAD_SELECT";
        }

        return "idx_" + std::to_string(index);
    }

    bool isGoodArg(std::tuple<Type, int, int> p) {
        return true;
    }

    bool isGoodArg(std::tuple<Type, int, int> p1, std::tuple<Type, int, int> p2) {
        return true;
    }

    bool isRedundant(std::vector<std::tuple<Type, int, int>> p1, std::vector<std::tuple<Type, int, int>> p2) {
        return false;
    }
};

#endif