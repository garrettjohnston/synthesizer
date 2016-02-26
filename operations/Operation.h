#ifndef __PIE_OPERATION_H__
#define __PIE_OPERATION_H__

#include <functional>
#include <list>
#include <string>

#include "../Type.h"
#include "../values/Value.h"

class Operation {
public:
	std::function<Value(std::vector<Value>)> f;
	std::vector<Type> argTypes;
	Type retType;
	std::string printType();
};

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
