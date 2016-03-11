#ifndef __PIE_SYNTHESIZER_H__
#define __PIE_SYNTHESIZER_H__

#include <vector>
#include <map>
#include <set>
#include <tuple>
#include <utility>

#include "programs/Program.h"
#include "ProgramContainer.h"
#include "operations/Operation.h"
#include "Type.h"

template<typename ResT, typename... ArgT>
class Synthesizer {
public:
    Synthesizer();

    // Function that does all the meat of the work, searching over all Programs until one is found
    // that satisfies the input/outputs pairs given in the samples vector.
    // samples -- a vector of pairs of input/outputs, casted as boost::any.
    Program findFittingProgram(std::vector<std::pair<std::vector<boost::any>, boost::any>> samples);

    void printAllOperations();
private:
    // Container that holds all programs
    static ProgramContainer* programContainer;

    // Adds an operation to the Synthesizer's list of operations to use during search for a Program
    void pushOperation(Operation *op);

    // Map from operations arg type to operations
    std::map<std::vector<Type>, std::vector<Operation*>> allOperations;
};

// static initialization
template<typename ResT, typename... ArgT>
ProgramContainer* Synthesizer<ResT, ArgT...>::programContainer = NULL;

#include "Synthesizer.hpp"
#endif
