#ifndef __PIE_PROGRAM_HPP__
#define __PIE_PROGRAM_HPP__

#include <vector>
#include <boost/any.hpp>

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
    for (auto child : children) {
        if (programContainer->get(child).containsInputVal) {
            containsInputVal = true;
            break;
        }
    }

}

// Evaluates this program with the given input values, first recursively calling it's children to evaluate themselves.
boost::any Program::evaluate(const std::vector<boost::any>& input) {
    // Check if this program is at level 0
    if (children.size() == 0) {
        return operation->f(input);
    } else {
        std::vector<boost::any> vals;
        for (auto child : children) {
            vals.push_back(programContainer->get(child).evaluate(input));
        }
        return operation->f(vals);
    }
}


Type Program::getType() { return type; }


// Returns true if the program satisfies all samples. Assumes that samples output type == program output type.
bool Program::satisfiesSamples(std::vector<std::pair<std::vector<boost::any>, boost::any>> samples) {
    for (auto pair : samples) {
        std::vector<boost::any>& input = pair.first;
        boost::any output = pair.second;

        if ( !isEqual(evaluate(input), output, type))
            return false;
    }
    return true;
}

// Returns a string of the return type of this program.
std::string Program::printableType() {
    return TypeNames[static_cast<int>(type)];
}

// Returns a string of the id of this program and the id's of it's children
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

// Returns a string of the actual function (with operators and values) that this program will execute
std::string Program::toString() {
     return operation->toString(children);
}

#endif