#ifndef __PIE_SYNTHESIZER_H__
#define __PIE_SYNTHESIZER_H__

#include <vector>
#include <map>

#include "programs/Program.h"
#include "ProgramContainer.h"
#include "operations/Operation.h"
#include "Type.h"

template<typename ResT, typename ArgT>
class Synthesizer {
public:
    // TODO pass in std::map<ArgT, ResT>& functionMap
    Synthesizer();
    Program findNewFeature();
    void pushOperation(Operation* op);
    void printAllOperations();

private:
    // Container that holds all programs
    static ProgramContainer* programContainer;

    // Map from operations arg type to operations
    std::map<std::vector<Type>, std::vector<Operation*>> allOperations;

    std::vector<Value> inputs;
};

// static initialization
template<typename ResT, typename ArgT>
ProgramContainer* Synthesizer<ResT, ArgT>::programContainer = NULL;

#include "Synthesizer.hpp"
#endif
