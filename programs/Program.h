#ifndef __PIE_PROGRAM_H__
#define __PIE_PROGRAM_H__

#include <functional>
#include <vector>
#include <string>
#include <map>

#include "../operations/Operation.h"
#include "../Type.h"
#include "../values/Value.h"

class ProgramContainer;

class Program {
public:
    Program();
    Program(Operation * op);
    Program(Operation* op, std::vector<std::tuple<Type, int, int>> ch);
    Value evaluate(std::vector<Value>& input);
    bool resolvesConflict();
    std::string printableType();
    std::string toString();
    std::string printId();
    Type getType();

    static int count;
    Type type;
    // Store children as a tuple of <Type, level, index> to retrieve it from programs vector
    std::vector<std::tuple<Type, int, int>> children;
    Operation* operation;
    int id;

    static ProgramContainer* programContainer;
};

// static initialization
int Program::count = 0;
ProgramContainer* Program::programContainer = NULL;

#endif
#include "Program.hpp"
