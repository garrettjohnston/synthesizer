#ifndef __PIE_SYNTHESIZER_H__
#define __PIE_SYNTHESIZER_H__

#include <vector>
#include <map>
#include <set>
#include <utility>

#include "programs/Program.h"
#include "ProgramContainer.h"
#include "operations/Operation.h"
#include "Type.h"

template<typename ResT, typename... ArgT>
class Synthesizer {
public:
    // TODO pass in std::map<ArgT, ResT>& functionMap
    Synthesizer();
    Program findNewFeature();
    void pushOperation(Operation* op);
    void printAllOperations();

private:
    bool resolvesConflict(Program& p);

    // Container that holds all programs
    static ProgramContainer* programContainer;

    // First vector holds all separate conflict sets.
    // Tuple (conflict set) is a pair:
    //  - First is vector of positive conflict inputs
    //  - Second is vector of negative conflict inputs
    // TODO: Do I want to use a set or unordered_set here for efficiency? idk
    std::vector<std::pair<std::vector<std::vector<Value>>, std::vector<std::vector<Value>>>> conflictSets;

    // Map from operations arg type to operations
    std::map<std::vector<Type>, std::vector<Operation*>> allOperations;

    std::vector<Value> inputs;
};

// static initialization
template<typename ResT, typename... ArgT>
ProgramContainer* Synthesizer<ResT, ArgT...>::programContainer = NULL;

#include "Synthesizer.hpp"
#endif
