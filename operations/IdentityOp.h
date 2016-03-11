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
// TODO: Think about making this generic. One constructor that takes a boost::any (and maybe the Type too)
    boost::any val;
    IdentityOp(int i) {
        val = boost::any(i);
        retType = Type::TInt;
        initFunction();
    }

    IdentityOp(bool b) {
        val = boost::any(b);
        retType = Type::TBool;
        initFunction();
    }

    IdentityOp(std::string s) {
        val = boost::any(s);
        retType = Type::TStr;
        initFunction();
    }

    void initFunction() {
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
