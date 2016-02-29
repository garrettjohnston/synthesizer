#ifndef __PIE_OPERATIONS_IDENTITY_OP_H__
#define __PIE_OPERATIONS_IDENTITY_OP_H__

#include <functional>
#include <vector>
#include <stdexcept>
#include <string>
#include <boost/any.hpp>

#include "Operation.h"
#include "../Type.h"
#include "../values/Value.h"


class IdentityOp: public Operation {
public:
  // TODO: Think about making this generic. One constructor that takes a Value (and maybe the Type too)
  Value val;
  IdentityOp(int i) {
    val = Value(i);
    retType = Type::TInt;
    initFunction();
  }

  IdentityOp(bool b) {
    val = Value(b);
    retType = Type::TBool;
    initFunction();
  }

  IdentityOp(std::string s) {
    val = Value(s);
    retType = Type::TStr;
    initFunction();
  }

  void initFunction() {
  	f = [this](std::vector<Value> args) {
  		return this->val;
  	};
  }

    std::string toString(std::vector<std::tuple<Type, int, int>> args) {
      if (args.size() != 0) {
        return "BAD_IDNTY";
      }

      return val.toString();
    }
};

#endif
