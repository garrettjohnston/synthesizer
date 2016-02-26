#ifndef __PIE_VALUE_H__
#define __PIE_VALUE_H__

#include <string>

#include "../Type.h"

class Value {
public:
	virtual Type getType() {}
	virtual std::string toString() {};
	virtual ~Value() {}
};

#endif
