#ifndef __PIE_OPERATION_H__
#define __PIE_OPERATION_H__

#include <functional>
#include "Type.h"

template<typename ResT, typename ArgT>
class Operation {
public:
	std::function<ResT(ArgT)> f;
	Type retType, leftType, rightType;
	
};

#endif
