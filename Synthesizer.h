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
    // TODO pass in std::map<ArgT, ResT>& functionMap
    Synthesizer();
    Program findNewFeature();
    std::vector<Program> getPrograms(Type returnType, int level);
    void pushOperation(Operation op);
    void pushProgram(Program p, int level);

private:
    // Map from Program return type to vector (by level) of vectors of Programs
    std::map<Type, std::vector<std::vector<Program>>> allPrograms;

    // Map from operations arg type to operations
    std::map<std::vector<Type>, std::vector<Operation>> allOperations;
};

#include "Synthesizer.hpp"
#endif
