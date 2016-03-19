#ifndef __PIE_PROGRAM_CONTAINER_HPP__
#define __PIE_PROGRAM_CONTAINER_HPP__

#include <tuple>
#include <vector>
#include <iostream>
#include <boost/any.hpp>

#include "ProgramContainer.h"
#include "programs/Program.h"
#include "utils/util.h"

ProgramContainer* ProgramContainer::getInstance() {
    if (!instance) {
        instance = new ProgramContainer();
    }
    return instance;
}

ProgramContainer::ProgramContainer() {

}

Program& ProgramContainer::get(std::tuple<Type, int, int> index) {
    return programs.at(std::get<0>(index)).at(std::get<1>(index)).at(std::get<2>(index));
}

std::vector<Program>& ProgramContainer::getPrograms(Type returnType, int level) {
    return programs.at(returnType).at(level);
}

int ProgramContainer::size(Type returnType, int level) {
    if (programs.count(returnType) == 0) {
        return 0;
    }
    return programs.at(returnType).at(level).size();
}

void ProgramContainer::push(Program p, int level) {
//    std::cout << "Program: " << p.printId() << " -- " << p.toString() << std::endl;
    // Currently doing this just to print the evaluated value. This makes run time much slower btw...
//    std::vector<boost::any> v;
//    v.push_back(boost::any(15));
//    v.push_back(boost::any(20));
//    v.push_back(boost::any(false));
//    std::cout << " evaluates to " << utils::toString(p.evaluate(v)) << std::endl;

    auto search = programs.find(p.getType());
    if (search != programs.end()) {
        auto& programsOfThisType = search->second;
        if (level > programsOfThisType.size() - 1) {  // Check if this level has been created yet.
            if (level == programsOfThisType.size()) {  // Check if this level is next empty spot in vector
                std::vector<Program> newVec;
                newVec.push_back(p);
                programsOfThisType.push_back(newVec);
            } else throw std::invalid_argument("Trying to add program to level " + std::to_string(level));
        } else {
            programsOfThisType.at(level).push_back(p);
        }
    } else {
        std::vector<std::vector<Program>> programsOfOneType;
        std::vector<Program> programsAtOneLevel;
        programsAtOneLevel.push_back(p);
        programsOfOneType.push_back(programsAtOneLevel);
        programs.insert({p.getType(), programsOfOneType});
    }
}

void ProgramContainer::printAllPrograms() {
    std::cout << std::endl << "Programs:" << std::endl;
    for (auto& it : programs) {
        std::cout << "Returning " << TypeNames[static_cast<int>(it.first)] << std::endl;

        int level = 0;
        for (auto programsAtLevel : it.second) {
            std::cout << "Level " << level << std::endl;
            for (auto program : programsAtLevel) {
                std::cout << "Program: " << program.printId() << " -- " << program.toString() << std::endl;
            }
            level++;
        }
    }
}

#endif