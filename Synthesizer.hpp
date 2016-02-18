#ifndef __PIE_SYNTHESIZER_CPP__
#define __PIE_SYNTHESIZER_CPP__

#include <vector>
#include <map>
#include <iostream>

#include "Synthesizer.h"
#include "programs/Program.h"
#include "programs/ZeroProgram.h"
#include "programs/OneProgram.h"
#include "programs/InputProgram.h"
#include "operations/AddOp.h"
#include "operations/MultiplyOp.h"
#include "operations/GreaterThanOp.h"
#include "operations/LessThanOp.h"
#include "operations/IntEqualsOp.h"

// Constructor
// TODO: think more about storing programs in vectors by Type (prog return type)
template<typename ResT, typename ArgT>
Synthesizer<ResT, ArgT>::Synthesizer() {
	std::vector<Program> level0Programs;
	level0Programs.push_back(ZeroProgram());
	level0Programs.push_back(OneProgram());
	level0Programs.push_back(InputProgram(0));
	
	std::vector<Operation> ops;
	
	pushOperation(AddOp());
	pushOperation(MultiplyOp());
	pushOperation(GreaterThanOp());
	pushOperation(LessThanOp());
	pushOperation(IntEqualsOp());
	std::cout << "I'm alive!";
	
	intPrograms.push_back(level0Programs);
}

// TODO: fully implement this
template<typename ResT, typename ArgT>
Program Synthesizer<ResT, ArgT>::findNewFeature() {
	// Check level 0 programs for viable features
	/*
	for (std::vector<Program>::iterator it = intPrograms.at(0); it != intPrograms.at(0).end(); it++) {
		if (it->resolvesConflict()) {
			return NULL;
		}
	}*/
	int level = 1;
	int count = 0;
	while(level < 2) {
	/*
		std::vector<Program> newPrograms;
		for (auto op : getOperations(IntegerT)) {
			for (auto program1 : getPrograms(level - 1, IntegerT)) {
				for (int innerLevel = 0; innerLevel < level; innerLevel++) {
					for (auto program2 : getPrograms(innerLevel, IntegerT)) {
						std::cout << " " << count << " ";
						Program newProgram(op, &program1, &program2);
						newPrograms.push_back(newProgram);
						count++;
					}
				}
			}
		}
		intPrograms.push_back(newPrograms);
	*/
	 	level++;
	}
	
	return NULL;
}


template<typename ResT, typename ArgT>
std::vector<Program> Synthesizer<ResT, ArgT>::getPrograms(int level, Type type) {
	switch(type) {
		case TInt:
			return intPrograms.at(level);
		case TBool:
			return boolPrograms.at(level);
		case TStr:
			return stringPrograms.at(level);
	}
}


// Adds an operation to the allOperations map
template<typename ResT, typename ArgT>
void Synthesizer<ResT, ArgT>::pushOperation(Operation op) {
	auto search = allOperations.find(op.argTypes);
	if (search != allOperations.end()) {
		auto vec = search->second;
		vec.push_back(op);
	} else {
		std::vector<Operation> newVec;
		newVec.push_back(op);
		allOperations.insert({op.argTypes, newVec});
	}
}
   

#endif
