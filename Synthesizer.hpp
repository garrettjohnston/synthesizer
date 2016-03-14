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
#include "operations/IdentityOp.h"
#include "operations/SelectorOp.h"
#include "operations/Operation.h"
#include "ProgramContainer.h"
#include "Type.h"
#include "Synthesizer.h"
#include "userDefinedTypes/List.hpp"
#include "operations/ListAddItemOp.h"

template<typename ResT, typename... ArgT>
Synthesizer<ResT, ArgT...>::Synthesizer() {
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


    pushOperation(new AddOp());
    pushOperation(new MultiplyOp());
    pushOperation(new GreaterThanOp());
//    pushOperation(new LessThanOp());
    pushOperation(new IntEqualsOp());
    pushOperation(new ListAddItemOp());

    printAllOperations();
}


template<typename ResT, typename... ArgT>
Program Synthesizer<ResT, ArgT...>::findFittingProgram(std::vector<std::pair<std::vector<boost::any>, boost::any>> samples) {

    // Add input values in to level 0 Programs.
    // NOTE: Could not find a good way to leverage C++'s built in type system and templates to do this.
    int index = 0;
    for (auto inputVal : samples[0].first) {
        programContainer->push(Program(new SelectorOp(index, getTypeOfAny(inputVal))), 0);
        index++;
    }

    // Check level 0 programs for a Program that satisfies the samples
    Type returnType = getTypeOfAny(samples[0].second);
    for (Program p : programContainer->getPrograms(returnType, 0)) {
        if (p.satisfiesSamples(samples)) {
            return p;
        }
    }

    int level = 1;

    // Could add a time limit here with the while loop
    while (level < 4) {
        std::cout << std::endl << "LEVEL " << level << std::endl;
        // For each set of operations separated by arg types
        for (auto it : allOperations) {
            std::vector<Type> inputTypes = it.first;
            std::vector<Operation *> operations = it.second;

            // For each operation in this set
            for (auto op : operations) {
                bool opIsRightReturnType = (returnType == op->retType);

                std::cout << std::endl << "New Operation: " << op->name() << op->printType() << std::endl;

                // Create vector of "children" to hold the child Programs of the new Program we are creating
                std::vector<std::tuple<Type, int, int>> children;

                // The first child must only consider programs from current level - 1 (if the operation is composable)
                int startLevel = op->isComposable ? level - 1 : 0;
                for ( ; startLevel < level; startLevel++) {
                    int child1NumPrograms = programContainer->size(inputTypes[0], startLevel);
                    for (int index = 0; index < child1NumPrograms; index++) {
                        // Create the tuple to represent the child 1 Program.
                        std::tuple<Type, int, int> child1{inputTypes[0], startLevel, index};

                        // Check if this program is sensible for the given operation
                        if (op->isGoodArg(child1)) {
                            children.push_back(child1);
                        } else {
                            continue;
                        }

                        // Assume only 1 or 2 inputs at this time. Generalize later if possible
                        if (inputTypes.size() == 1) {
                            Program newProgram(op, children);

                            // Check if this program satisfies all sample input/outputs.
                            if (opIsRightReturnType && newProgram.satisfiesSamples(samples)) {
                                return newProgram;
                            }
                            programContainer->push(newProgram, level);
                        }

                        else if (inputTypes.size() == 2) {
                            // Put dummy data in the second spot to overwrite in loop
                            std::tuple<Type, int, int> dummy{Type::TInt, -1, -1};
                            children.push_back(dummy);

                            // The second child can be a Program from any previous level
                            for (int anyLevel = 0; anyLevel < level; anyLevel++) {
                                int child2NumPrograms = programContainer->size(inputTypes[1], anyLevel);

                                // If we have a symmetric operation, skip any instances of repeat Programs
                                // that are simply on swapped sides of the operator (e.g. A == B, and B == A)
                                int index2 = 0;
                                if (op->isSymmetric && anyLevel == startLevel) {
                                    index2 = index;
                                }
                                for (; index2 < child2NumPrograms; index2++) {
                                    // Create the tuple to represent the child 2 Program
                                    std::tuple<Type, int, int> child2{inputTypes[1], anyLevel, index2};

                                    // Check that both args are good for this operator
                                    if (op->isGoodArg(child1, child2)) {
                                        children.at(1) = child2;

                                        Program newProgram(op, children);
                                        if (opIsRightReturnType && newProgram.satisfiesSamples(samples)) {
                                            return newProgram;
                                        }
                                        programContainer->push(newProgram, level);
                                    }
                                }
                            }
                        }

                        else { //TODO: Can probably handle this more gracefully
                            throw std::invalid_argument("Operators with > 2 args not currently accepted.");
                        }
                        children.clear();
                    }
                }
            }
        }
        level++;
    }
    //programContainer->printAllPrograms();
    throw std::runtime_error("Could not find program within allotted time");
}


// Adds an operation to the allOperations map
template<typename ResT, typename... ArgT>
void Synthesizer<ResT, ArgT...>::pushOperation(Operation *op) {
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


template<typename ResT, typename... ArgT>
void Synthesizer<ResT, ArgT...>::printAllOperations() {
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
