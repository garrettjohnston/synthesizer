#ifndef __PIE_INPUT_PROGRAM_H__
#define __PIE_INPUT_PROGRAM_H__

#include <functional>
#include <tuple>

#include "Program.h"
#include "../operations/SelectorOp.h"
#include "../values/Value.h"

//template<typename inputTypes...>
class InputProgram: public Program {
public:
  InputProgram(int i) {
    index = i;
  }
  
  Value evaluate(std::vector<Value> inputs) {
  	return VInt(17);
  };	

  int index;
};

#endif
