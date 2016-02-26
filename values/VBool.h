#ifndef __PIE_VALUE_VBOOL_H__
#define __PIE_VALUE_VBOOL_H__

#include <string>

#include "Value.h"
#include "../Type.h"

class VBool : public Value {
public:
	VBool(bool v): val(v) {};
	bool val;
	Type getType() { return Type::TBool; }
	std::string toString() {
		std::string s("Bool ");
		s += std::to_string(val);
	}
};

#endif
