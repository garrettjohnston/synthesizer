#ifndef __PIE_PROGRAM_CONTAINER_H__
#define __PIE_PROGRAM_CONTAINER_H__

#include <tuple>

#include "Type.h"

class ProgramContainer {
public:
    static ProgramContainer* getInstance();
    Program& get(std::tuple<Type, int, int>);
    std::vector<Program>& getPrograms(Type returnType, int level);
    int size(Type returnType, int level);
    void push(Program program, int level);
    void printAllPrograms();
private:
    ProgramContainer();

    static ProgramContainer* instance;
    std::map<Type, std::vector<std::vector<Program>>> programs;
};

ProgramContainer* ProgramContainer::instance = NULL;

#endif
#include "ProgramContainer.hpp"