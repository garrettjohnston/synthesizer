#ifndef __PIE_SYNTHESIZER_H__
#define __PIE_SYNTHESIZER_H__

#include <vector>
#include <map>

#include "programs/Program.h"
#include "operations/Operation.h"
#include "Type.h"

template<typename ResT, typename ArgT>
class Synthesizer {
public:
  // Constructor
  // TODO pass in std::map<ArgT, ResT>& functionMap
  Synthesizer();
  Program findNewFeature();
  std::vector<Program> getPrograms(int level, Type type);
  
  // Vector of Programs by level
  std::vector<std::vector<Program>> intPrograms;
  std::vector<std::vector<Program>> boolPrograms;
  std::vector<std::vector<Program>> stringPrograms; 
  
  // Group operations by arg type
  std::map<std::vector<Type>, std::vector<Operation>> allOperations;
  void pushOperation(Operation op);
};

#include "Synthesizer.hpp"
#endif
