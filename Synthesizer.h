#ifndef __PIE_SYNTHESIZER_H__
#define __PIE_SYNTHESIZER_H__

#include <vector>
#include <map>

#include "Program.h"
#include "Operation.h"
#include "Type.h"

template<typename ResT, typename ArgT>
class Synthesizer {
public:
  // Constructor
  Synthesizer(std::map<ArgT, ResT> functionMap);
  Program findNewFeature();
  std::vector<Operation<ResT, ArgT>> getOperations(Type type);
  
  // Vector of Programs by level
  std::vector<std::vector<Program>> intPrograms;
  std::vector<std::vector<Program>> boolPrograms;
  std::vector<std::vector<Program>> stringPrograms; 
  
  // Vector of operations by type returned
  std::vector<Operation<ResT, ArgT>> intOperations;
  std::vector<Operation<ResT, ArgT>> boolOperations;
  std::vector<Operation<ResT, ArgT>> stringOperations;
};

#endif
