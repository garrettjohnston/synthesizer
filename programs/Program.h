#ifndef __PIE_PROGRAM_H__
#define __PIE_PROGRAM_H__

#include <functional>
#include <vector>
#include <string>
#include <map>

#include "../operations/Operation.h"
#include "../Type.h"

class ProgramContainer;

class Program {
public:
    // Constructors
    Program();
    Program(Operation * op);
    Program(Operation* op, std::vector<std::tuple<Type, int, int>> ch);

    // Evaluates the Program with the given input
    boost::any evaluate(const std::vector<boost::any>& input);

    // Returns true if the given input/output samples are satisfied by this Program. Else false.
    bool satisfiesSamples(std::vector<std::pair<std::vector<boost::any>, boost::any>> samples);

    //
    Type getType();

    // Helpful debugging print statements
    std::string printableType();
    std::string toString();
    std::string printId();

    // The return Type of this program (defined in Type.h)
    Type type;

    // Store children as a tuple of (Type, level, index) to retrieve it from the programContainer
    std::vector<std::tuple<Type, int, int>> children;

    // Pointer to operation (held in Synthesizer)
    Operation* operation;

    // A number that uniquely identifies this Program. Taken from "count" when constructed.
    int id;

    // Value is true if this program or any of its children contains an input value (i.e. SelectorOp)
    bool containsInputVal = false;

    static ProgramContainer* programContainer;
    static int count;
};

// static initialization
int Program::count = 0;
ProgramContainer* Program::programContainer = NULL;

#endif
#include "Program.hpp"
