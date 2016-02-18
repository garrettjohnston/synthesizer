#ifndef __PIE_VALUE_VINT_H__
#define __PIE_VALUE_VINT_H__

#include "Value.h"

class VInt : public Value {
public:
	VInt(int v): val(v) {};
	int val;
	int something() { return 1; }
};

#endif
