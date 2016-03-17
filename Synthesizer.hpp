#ifndef __PIE_SYNTHESIZER_CPP__
#define __PIE_SYNTHESIZER_CPP__

#include <vector>
#include <map>
#include <iostream>
#include <iterator>
#include <tuple>
#include <utility>
#include <boost/any.hpp>
#include <stdexcept>

#include "programs/Program.h"
#include "operations/AddOp.h"
#include "operations/MultiplyOp.h"
#include "operations/GreaterThanOp.h"
#include "operations/LessThanOp.h"
#include "operations/IntEqualsOp.h"
#include "operations/primitive/IdentityOp.h"
#include "operations/primitive/SelectorOp.h"
#include "operations/Operation.h"
#include "ProgramContainer.h"
#include "Type.h"
#include "Synthesizer.h"
#include "userDefinedTypes/List.hpp"
#include "operations/ListAddItemOp.h"

Synthesizer::Synthesizer() {
    Synthesizer::programContainer = ProgramContainer::getInstance();
    Program::programContainer = ProgramContainer::getInstance();
    Operation::programContainer = ProgramContainer::getInstance();


    // Add primitive values to level 0 of search tree
    programContainer->push(Program(new IdentityOp(0)), 0);
    programContainer->push(Program(new IdentityOp(1)), 0);
    programContainer->push(Program(new IdentityOp(true)), 0);
    programContainer->push(Program(new IdentityOp(false)), 0);
    programContainer->push(Program(new IdentityOp(std::string(""))), 0);
    programContainer->push(Program(new IdentityOp(List())), 0);


    // Put all operations here
    pushOperation(new AddOp());
    pushOperation(new MultiplyOp());
    pushOperation(new GreaterThanOp());
//    pushOperation(new LessThanOp());
    pushOperation(new IntEqualsOp());
    pushOperation(new ListAddItemOp());

    printAllOperations();
}


void printVector(std::string s, std::vector<int> v) {
    std::cout << s;
    for (auto i : v)
        std::cout << " " << i;
    std::cout << std::endl;
}

Program Synthesizer::findFittingProgram(std::vector<std::pair<std::vector<boost::any>, boost::any>> samples) {

    // Add input values in to level 0 Programs.
    // NOTE: Could not find a good way to leverage C++'s built in type system and templates to do this.
    int index = 0;
    for (auto inputVal : samples[0].first) {
        Program p(Program(new SelectorOp(index, getTypeOfAny(inputVal))));
        p.containsInputVal = true;
        programContainer->push(p, 0);
        index++;
    }

    // Check level 0 programs for a Program that satisfies the samples
    Type returnType = getTypeOfAny(samples[0].second);
    for (Program p : programContainer->getPrograms(returnType, 0)) {
        if (p.satisfiesSamples(samples)) {
            return p;
        }
    }

    // level is the current level we are building programs for
    int level = 1;

    // Could add a time limit here with the while loop
    while (level < 4) {
        std::cout << std::endl << "LEVEL " << level << std::endl;
        // For each set of operations separated by arg types
        for (auto it : allOperations) {
            std::vector<Type> inputTypes = it.first;
            std::vector<Operation *> operations = it.second;
            int numArgs = (int)inputTypes.size();

            // For each operation in this set
            for (auto op : operations) {
                bool opIsRightReturnType = (returnType == op->retType);
                bool isSymmetric = op->isSymmetric;

                std::cout << std::endl << "Operation: " << op->name() << op->printType() << std::endl;

                // Create vector of "children" to hold the child Programs of the new Program we are creating
                std::vector<std::tuple<Type, int, int>> children;

                // Add dummy data to children to overwrite later
                std::tuple<Type, int, int> dummy {Type::TInt, -1, -1};
                for (int i = 0; i < numArgs; i++) {
                    children.push_back(dummy);
                }

                // Represents the max level we are pulling from for each argument. Generally this is always the same number.
                std::vector<int> numLevels;
                for (int i = 0; i < numArgs; i++) {
                    numLevels.push_back(level - 1);
                }
//                printVector("numLevels", numLevels);

                // Represents the current levels we are pulling programs from, for each argument in the operation
                std::vector<int> argLevels;

                // If the operation is symmetric, then we can force the first argument to always be from level - 1
                // The rest of the args start at level 0
                argLevels.push_back(isSymmetric ? level - 1 : 0);
                for (int i = 1; i < numArgs; i++) {
                    argLevels.push_back(0);
                }

                // Loop until all level combinations are exhausted
                while (argLevels != std::vector<int>()) {
                    // Ensure at least ONE level is from the max: level - 1
                    while (!atLeastOneMax(argLevels, numLevels)) {
                        argLevels = getNextCombo(isSymmetric, argLevels, numLevels);
                    }

                    bool allLevelsSame = std::adjacent_find(argLevels.begin(), argLevels.end(), std::not_equal_to<int>() ) == argLevels.end();
//                    printVector("argLevels", argLevels);
                    // Represents sizes of the current level each arg is pulling from.
                    std::vector<int> levelSizes;
                    for (int argNum = 0; argNum < numArgs; argNum++) {
                        levelSizes.push_back( programContainer->size(inputTypes[argNum], argLevels[argNum]) - 1);
                    }
//                    printVector("levelSizes", levelSizes);

                    // Represents, for each argument in the operation, the index of the program we are grabbing.
                    std::vector<int> programIndices;

                    // Even if the op is symmetric, we still want to cover all program combinations at a given level.
                    // Initialize program indices.
                    for (int i = 0; i < numArgs; i++) {
                        programIndices.push_back(0);
                    }

                    // Loop through all programs at the given level combination
                    while (programIndices != std::vector<int>()) {
//                        printVector("programIndices", programIndices);

                        for (int argNum = 0; argNum < numArgs; argNum++) {
                            std::tuple<Type, int, int> child {inputTypes[argNum], argLevels[argNum], programIndices[argNum]};
                            children[argNum] = child;
                        }

                        // Check if children are good fit!
                        if (op->areGoodArgs(children)) {

                            Program newProgram(op, children);
                            if (opIsRightReturnType && newProgram.satisfiesSamples(samples)) {
                                return newProgram;
                            }
                            programContainer->push(newProgram, level);
                        }
                        programIndices = getNextCombo(isSymmetric && allLevelsSame, programIndices, levelSizes);
                    }

                    argLevels = getNextCombo(isSymmetric, argLevels, numLevels);
                }
            }
        }
        level++;
    }
    //programContainer->printAllPrograms();
    throw std::runtime_error("Could not find program within allotted time");
}


// Checks that at least one digit in current contains a max value, as defined in the "max" vector
// @param current - vector of digits
// @param max - vector of maximum values that digits in current can increase up to
bool Synthesizer::atLeastOneMax(std::vector<int> current, std::vector<int> max) {
    for (int i = 0; i < current.size(); i++) {
        if (current[i] == max[i])
            return true;
    }
    return false;
}


// Helper function to return the next valid number combination.
// EX: getNextCombo(false, {0,0}, {2,4}) --> {0,1}
// EX: getNextCombo(false, {0,4}, {2,4}) --> {1,0}
// EX: getNextCombo(false, {2,4}, {2,4}) --> {}
// The isSymmetric part is confusing, but basically forces the next combination to not have been a permutation
// of any previously returned combination.
// EX: getNextCombo(true, {1,4}, {2,4}) --> {2,2},because the next ones {2,0}, {2,1} have already come up as {0,2}, {1,2}.
std::vector<int> Synthesizer::getNextCombo(bool isSymmetric, std::vector<int> current, std::vector<int> max) {
    if (current.size() != max.size()) {
        throw std::invalid_argument("Vector size mismatch! current.size() != max.size()");
    }

    int i = current.size() - 1;
    while (i >= 0) {
        // General case, if we can increase a digit, do it.
        if (current[i] != max[i]) {
            current[i]++;
            // If symmetric, set all numbers to RIGHT equal to this number. This avoids repeating permutations
            if (isSymmetric)
                for (int j = i+1; j < current.size(); j++) {
                    current[j] = current[i];
                }
            return current;
        }
        // If we have reached the max digit at position i, try the one to the left.
        else {
            current[i] = 0;
            i--;
        }
    }
    // Return empty vector when there are no more valid combinations
    return std::vector<int>();
}


// Adds an operation to the allOperations map
void Synthesizer::pushOperation(Operation *op) {
    auto search = allOperations.find(op->argTypes);
    if (search != allOperations.end()) {
        auto &vec = search->second;
        vec.push_back(op);
    } else {
        std::vector<Operation *> newVec;
        newVec.push_back(op);
        allOperations.insert({op->argTypes, newVec});
    }
}


void Synthesizer::printAllOperations() {
    std::cout << "Operations:" << std::endl;
    for (auto it = allOperations.begin(); it != allOperations.end(); it++) {
        std::cout << it->second.size();
        std::cout << " (";
        for (auto it2 = it->first.begin(); it2 != it->first.end(); it2++) {
            std::cout << TypeNames[static_cast<int>(*it2)];
            if (std::next(it2) != it->first.end()) std::cout << ", ";
        }
        std::cout << ") --> ANY ops" << std::endl;
        std::cout << "(";
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
            std::cout << (*it2)->printType();
            if (std::next(it2) != it->second.end()) std::cout << ", ";
        }
        std::cout << ")" << std::endl;
    }
}


#endif
