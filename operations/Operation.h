#ifndef __PIE_OPERATION_H__
#define __PIE_OPERATION_H__

#include <functional>
#include <list>
#include <string>
#include <vector>
#include <tuple>
#include <boost/any.hpp>

#include "../Type.h"

class ProgramContainer;

class Operation {
public:
    std::function<boost::any(std::vector<boost::any>)> f;
	std::vector<Type> argTypes;
	Type retType;
    bool isSymmetric;

	std::string printType();
	virtual std::string toString(std::vector<std::tuple<Type, int, int>>) = 0;
	virtual std::string name() = 0;
    virtual bool areGoodArgs(std::vector<std::tuple<Type, int, int>> program) = 0;

    virtual bool isRedundant(std::vector<std::tuple<Type, int, int>> p1, std::vector<std::tuple<Type, int, int>> p2) = 0;

    static ProgramContainer* programContainer;
};

ProgramContainer* Operation::programContainer = NULL;

std::string Operation::printType() {
	std::string s("(");
	for (auto it = argTypes.begin(); it != argTypes.end(); it++) {
		s += TypeNames[static_cast<int>(*it)];
		if (std::next(it) != argTypes.end()) s += " ";
	}
	s += ") -> " + TypeNames[static_cast<int>(retType)];
	return s;
}

#endif
