#ifndef __PIE_SELECTOR_OP_H__
#define __PIE_SELECTOR_OP_H__

#include <functional>
#include <vector>

#include "Operation.h"

class SelectorOp: public Operation<int, int> {
public:  
  SelectorOp(std::vector<int> in) {
  	inputs = in;
  	f = [](int i) { return i*100; };
  }
  
  std::vector<int> inputs;
};

#endif
