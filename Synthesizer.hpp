#ifndef __PIE_SYNTHESIZER_HPP__
#define __PIE_SYNTHESIZER_HPP__

#include <vector>
#include <map>
#include <iostream>

#include "Synthesizer.h"
#include "Program.h"
#include "ZeroProgram.h"
#include "OneProgram.h"
#include "InputProgram.h"
#include "AddOp.h"
#include "MultiplyOp.h"
#include "GreaterThanOp.h"
#include "LessThanOp.h"
#include "IntEqualsOp.h"

// Constructor
// TODO: 
template<typename ResT, typename ArgT>
Synthesizer<ResT, ArgT>::Synthesizer(std::map<ArgT,ResT> functionMap) {
	std::vector<Program> level0Programs;
	level0Programs.push_back(ZeroProgram());
	level0Programs.push_back(OneProgram());
	level0Programs.push_back(InputProgram(0));
	
	intOperations.push_back(AddOp());
	intOperations.push_back(MultiplyOp());
	boolOperations.push_back(GreaterThanOp());
	boolOperations.push_back(LessThanOp());
	boolOperations.push_back(IntEqualsOp());
	
	intPrograms.push_back(level0Programs);
}

// TODO: fully implement this
template<typename ResT, typename ArgT>
Program Synthesizer<ResT, ArgT>::findNewFeature() {
	// Check level 0 programs for viable features
	for (std::vector<Program>::iterator it = intPrograms.at(0); it != intPrograms.at(0).end(); it++) {
		if (it->resolvesConflict()) {
			return NULL;
		}
		std::cout << "Hello there";
		
	}
	int level = 1;
	while(level < 5) {
	/*
		for op : BinaryOps {
			for Program p1 : programs.level(l-1).type(op.inputType) {
				for level L in 0-level l-1 {
					for Program p2 : programs.level(L).type(op.inputType) {
						new Program(op, p1, p2).addToList(L, returnType).
				}
			}
		}
	*/
	 	// construct list of programs/functions at level level
	 	// for each operation available, take all from level level - 1,
	 	// as left operand, and any others as right operand.
	 	// Just go through the lists grabbing the ones with the right
	 	// return values that match the operation signature
	 	level++;
	}
	
	return NULL;
}


template<typename ResT, typename ArgT>
std::vector<Operation<ResT, ArgT>> Synthesizer<ResT, ArgT>::getOperations(Type type) {
	switch(type) {
		case IntegerT:
			return intOperations;
		case BooleanT:
			return boolOperations;
		case StringT:
			return stringOperations;
	}
}
   

#endif
