#ifndef __PIE_PROGRAM_H__
#define __PIE_PROGRAM_H__

#include <functional>
#include <vector>
#include <string>

#include "../operations/Operation.h"
#include "../Type.h"
#include "../values/Value.h"

class Program {
public:
    Program();
    Program(Operation op, std::vector<Program*> ps);
    virtual Value evaluate(std::vector<Value> input);
    bool resolvesConflict();
    Type getType();
    std::string printableType();
    std::string toString();

    static int count;
    std::vector<Program*> children;
    Operation operation;
    int id;
};


Program::Program() {
    id = count++;
}


Program::Program(Operation op, std::vector<Program*> ps): operation(op), children(ps) {
    id = count++;
}


Value Program::evaluate(std::vector<Value> input) {
    std::vector<Value> vals;
    for (auto &it : children) {
        vals.push_back(it->evaluate(input));
    }
    return operation.f(vals);
}


Type Program::getType() {
    return operation.retType;
}


bool Program::resolvesConflict() {
    return false;
}


std::string Program::printableType() {
    return TypeNames[static_cast<int>(operation.retType)];
}


std::string Program::toString() {
    std::string s("id ");
    if (children.size() == 0) {
        s += std::to_string(id);
    } else if (children.size() == 1) {
        s += std::to_string(id) + ", L " + std::to_string(children[0]->id);
    } else if (children.size() == 2) {
        s += std::to_string(id) + ", L " + std::to_string(children[0]->id) + ", R " + std::to_string(children[1]->id);
    } else {
        s += ("More than 2 children");
    }
    return s;
}

int Program::count = 0;
#endif
