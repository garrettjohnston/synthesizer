#ifndef __PIE_PROGRAM_H__
#define __PIE_PROGRAM_H__

#include <functional>
#include <vector>

#include "../operations/Operation.h"
#include "../Type.h"
#include "../values/Value.h"

class Program {
public:
  // Constructor
  Program() {} ;
  Program(Operation op, std::vector<Program*> ps): operation(op), children(ps) {}
  Value evaluate(std::vector<Value> input);
  bool resolvesConflict() { return false; }
  
  std::vector<Program*> children;
  Operation operation;
  Type getType();
};


#endif
