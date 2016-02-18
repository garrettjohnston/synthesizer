#ifndef __PIE_VALUE_VBOOL_H__
#define __PIE_VALUE_VBOOL_H__

#include "Value.h"

class VBool : public Value {
public:
	VBool(bool v): val(v) {};
	bool val;
	int something() { return 1; }
};

#endif
