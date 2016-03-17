#ifndef __PIE_OPERATIONS_IDENTITY_OP_H__
#define __PIE_OPERATIONS_IDENTITY_OP_H__

#include <functional>
#include <vector>
#include <stdexcept>
#include <string>
#include <boost/any.hpp>

#include "Operation.h"
#include "../Type.h"
#include "../utils/util.h"


class IdentityOp: public Operation {
public:
    boost::any val;
    IdentityOp(boost::any v) {
        val = v;
        retType = getTypeOfAny(v);
        f = [this](std::vector<boost::any> args) {
            return this->val;
        };
    }

    std::string toString(std::vector<std::tuple<Type, int, int>> args) {
        if (args.size() != 0) {
            return "BAD_IDNTY";
        }

        return utils::toString(val);
    }

    std::string name() {
        return "IdentityOp";
    }

    bool areGoodArgs(std::vector<std::tuple<Type, int, int>> program) {
        return true;
    }

    bool isRedundant(std::vector<std::tuple<Type, int, int>> p1, std::vector<std::tuple<Type, int, int>> p2) {
        return false;
    }
};

#endif
