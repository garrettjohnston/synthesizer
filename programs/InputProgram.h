#ifndef __PIE_INPUT_PROGRAM_H__
#define __PIE_INPUT_PROGRAM_H__

#include <functional>
#include <tuple>

#include "Program.h"
#include "../operations/SelectorOp.h"
#include "../values/Value.h"
#include "../Type.h"

//template<typename inputTypes...>
class InputProgram: public Program {
public:
  InputProgram(int i) {
    operation = SelectorOp(i);
  }
  
  virtual Value evaluate(std::vector<Value> inputs) {
  	return operation.f(inputs);
  };

  // Override this function
  // TODO: make this general to return whatever type the input is. MAybe add input type as parameter to constructor
  virtual Type getType() {
  	return Type::TInt;
  }
};

#endif
