#ifndef __PIE_VALUE_VSTR_H__
#define __PIE_VALUE_VSTR_H__

#include <string>

#include "Value.h"

class VStr : public Value {
public:
	VStr(std::string v): val(v) {};
	std::string val;
	int something() { return 1; }
};

#endif
