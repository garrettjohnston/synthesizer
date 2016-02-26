#ifndef __PIE_VALUE_VSTR_H__
#define __PIE_VALUE_VSTR_H__

#include <string>

#include "Value.h"
#include "../Type.h"

class VStr : public Value {
public:
	VStr(std::string v): val(v) {};
	std::string val;
	Type getType() { return TStr; }
	std::string toString() {
		std::string s("Str " + val);
	}
};

#endif
