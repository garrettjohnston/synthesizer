#ifndef __PIE_INPUT_PROGRAM_H__
#define __PIE_INPUT_PROGRAM_H__

#include <functional>
#include <tuple>

#include "Program.h"
#include "SelectorOp.h"

//template<typename inputTypes...>
class InputProgram: public Program {
public:
  InputProgram(int i) {
    index = i;
  }
  
  int evaluate(std::tuple<int> inputs) {
  	return std::get<0>(inputs);
  };	

  int index;
};

#endif
