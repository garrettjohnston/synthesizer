#ifndef __PIE_PROGRAM_HPP__
#define __PIE_PROGRAM_HPP__

#include "../ProgramContainer.h"
#include "Program.h"

Program::Program() {
    id = count++;
}

Program::Program(Operation* op) : Program(){
    operation = op;
    type = op->retType;
}

Program::Program(Operation* op, std::vector<std::tuple<Type, int, int>> ch): Program(op) {
    children = ch;
}


Value Program::evaluate(std::vector<Value>& input) {
    // Check if this program is at level 0
    if (children.size() == 0) {
        return operation->f(input);
    } else {
        std::vector<Value> vals;
        for (auto child : children) {
            vals.push_back(programContainer->get(child).evaluate(input));
        }
        return operation->f(vals);
    }
}


Type Program::getType() { return type; }


bool Program::resolvesConflict() {
    return false;
}


std::string Program::printableType() {
    return TypeNames[static_cast<int>(type)];
}


std::string Program::printId() {
    std::string s("id ");
    if (children.size() == 0) {
        s += std::to_string(id);
    } else if (children.size() == 1) {
        s += std::to_string(id) + ", L " + std::to_string(programContainer->get(children[0]).id);
    } else if (children.size() == 2) {
        s += std::to_string(id) + ", L " + std::to_string(programContainer->get(children[0]).id)
                                + ", R " + std::to_string(programContainer->get(children[1]).id);
    } else {
        s += ("More than 2 children");
    }
    return s;
}

std::string Program::toString() {
     return operation->toString(children);
}

#endif