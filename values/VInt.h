#ifndef __PIE_VALUE_VINT_H__
#define __PIE_VALUE_VINT_H__

#include <string>

#include "Value.h"
#include "../Type.h"

class VInt : public Value {
public:
	VInt(int v): val(v) {};
	int val;
	Type getType() { return Type::TInt; }
	std::string toString() {
		std::string s("Int ");
		s += std::to_string(val);
	}
};

#endif
