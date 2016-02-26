#ifndef __PIE_INT_PROGRAM_H__
#define __PIE_INT_PROGRAM_H__

#include <functional>
#include <vector>

#include "Program.h"
#include "../operations/IdentityOp.h"
#include "../values/VInt.h"

class IntProgram: public Program {
public:
	int val;
	IntProgram(int v) {
		val = v;
		operation = IdentityOp();
	}

	virtual Value evaluate(std::vector<Value> input) {
		std::cout << "Evaluating IntProgram";
		return VInt(val);

		//TODO: This (below) is all kind of silly....
		// Can't I just say "return VInt(v);"
		std::vector<Value> values;
		values.push_back(VInt(val));
		return operation.f(values);
	};

};

#endif
