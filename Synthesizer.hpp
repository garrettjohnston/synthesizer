#ifndef __PIE_SYNTHESIZER_CPP__
#define __PIE_SYNTHESIZER_CPP__

#include <vector>
#include <map>
#include <iostream>
#include <iterator>
#include <tuple>
#include <utility>
#include <boost/any.hpp>

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
#include "values/Value.h"
#include "Synthesizer.h"

template<typename ResT, typename... ArgT>
Synthesizer<ResT, ArgT...>::Synthesizer() {
    Synthesizer::programContainer = ProgramContainer::getInstance();
    Program::programContainer = ProgramContainer::getInstance();
    Operation::programContainer = ProgramContainer::getInstance();

    // TODO: Take inputs or map as input to Synthesizer
    inputs.push_back(Value(15));
    inputs.push_back(Value(30));

    programContainer->push(Program(new IdentityOp(0)), 0);
    programContainer->push(Program(new IdentityOp(1)), 0);
    programContainer->push(Program(new IdentityOp(true)), 0);
    programContainer->push(Program(new IdentityOp(false)), 0);
    programContainer->push(Program(new SelectorOp(0, Type::TInt)), 0);
    programContainer->push(Program(new SelectorOp(1, Type::TInt)), 0);


    pushOperation(new AddOp());
    pushOperation(new MultiplyOp());
    pushOperation(new GreaterThanOp());
//    pushOperation(new LessThanOp());
    pushOperation(new IntEqualsOp());

    printAllOperations();
}

// TODO: fully implement this
template<typename ResT, typename... ArgT>
Program Synthesizer<ResT, ArgT...>::findNewFeature() {
    // Check level 0 programs for viable features
    /*
    for (std::vector<Program>::iterator it = intPrograms.at(0); it != intPrograms.at(0).end(); it++) {
        if (it->resolvesConflict()) {
            return NULL;
        }
    }*/
    int level = 1;
    while (level < 4) {
        std::cout << std::endl << "LEVEL " << level << std::endl;
        for (auto it = allOperations.begin(); it != allOperations.end(); it++) {
            std::vector<Type> inputTypes = it->first;
            std::vector<Operation *> operations = it->second;

            for (auto op : operations) {
                std::cout << std::endl << "New Operation: " << op->printType() << std::endl;
                std::vector<std::tuple<Type, int, int>> children;

                int numPrograms = programContainer->size(inputTypes[0], level - 1);
                for (int index = 0; index < numPrograms; index++) {
                    std::tuple<Type, int, int> child1{inputTypes[0], level - 1, index};
                    if (op->isGoodArg(child1)) {
                        children.push_back(child1);
                    } else {
                        continue;
                    }

                    // Assume only 1 or 2 inputs at this time. Generalize later if possible
                    if (inputTypes.size() == 1) {
                        programContainer->push(Program(op, children), level);
                    }
                    else if (inputTypes.size() == 2) {
                        std::tuple<Type, int, int> dummy{Type::TInt, -1, -1};
                        children.push_back(dummy); // Put dummy data in to overwrite in loop

                        for (int anyLevel = 0; anyLevel < level; anyLevel++) {
                            int numPrograms2 = programContainer->size(inputTypes[1], anyLevel);

                            int index2 = 0;
                            if (op->isSymmetric && anyLevel == level - 1) {
                                index2 = index;
                            }
                            for (; index2 < numPrograms2; index2++) {
                                std::tuple<Type, int, int> child2{inputTypes[1], anyLevel, index2};
                                if (op->isGoodArg(child1, child2)) {
                                    children.at(1) = child2;
                                    programContainer->push(Program(op, children), level);
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
        level++;
    }
    //programContainer->printAllPrograms();
    return Program();
}


// Returns {true, Program_index} if the given Program resolves all conflicts.
// Returns {false, undefined} if the given Program does NOT resolve all conflicts.
// TODO: If it resolves ONE conflict set, should we return it? Otherwise we have to solve all conflict sets simultaneously
// TODO: Not sure whether to assume that a boolean Program is passed in, or just check that case inside here.
template<typename ResT, typename... ArgT>
bool Synthesizer<ResT, ArgT...>::resolvesConflict(Program& p) {
    if (p.operation->retType != Type::TBool)
        return false;

    for (auto conflictSet : conflictSets) {
        bool truthValue = boost::any_cast<bool>(conflictSet.first[0]);
        for (auto positiveConflict : conflictSet.first) {
            bool b = boost::any_cast<bool>(p.evaluate(positiveConflict));
            if (b != truthValue)
                return false;
        }

        for (auto negativeConflict : conflictSet.second) {
            bool b = boost::any_cast<bool>(p.evaluate(negativeConflict));
            if (b == truthValue)
                return false;
        }
    }

    return true;
};


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
