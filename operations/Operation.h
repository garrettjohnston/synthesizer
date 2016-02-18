#ifndef __PIE_OPERATION_H__
#define __PIE_OPERATION_H__

#include <functional>
#include <list>

#include "../Type.h"
#include "../values/Value.h"

class Operation {
public:
	std::function<Value(std::vector<Value>)> f;
	std::vector<Type> argTypes;
	Type retType;
};

#endif
