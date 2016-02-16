#ifndef __PIE_PROGRAM_H__
#define __PIE_PROGRAM_H__

#include <functional>
#include <tuple>

#include "Operation.h"
#include "Type.h"

// Other possible names: Function, Feature
//template<typename ResT>
class Program {
public:
  // Constructor
  Program() {} ;
  int evaluate(std::tuple<int> input);
  bool resolvesConflict();
  
  Program* left;
  Program* right;
  Operation<int, int> operation;
  Type getType();
};

bool Program::resolvesConflict() {
	return false;
}


#endif
