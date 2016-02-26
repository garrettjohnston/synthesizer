#ifndef __PIE_SYNTHESIZER_CPP__
#define __PIE_SYNTHESIZER_CPP__

#include <vector>
#include <map>
#include <iostream>
#include <iterator>

#include "Synthesizer.h"
#include "programs/Program.h"
#include "programs/IntProgram.h"
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
	inputs.push_back(VInt(76));

	std::cout << "pushing int program" << std::endl;
	pushProgram(IntProgram(0), 0);
	pushProgram(IntProgram(1), 0);
	pushProgram(InputProgram(0), 0);

	std::cout << "Programs:" << std::endl;
	for (auto it = allPrograms.begin(); it != allPrograms.end(); it++) {
		std::cout << "(" << (int)it->first << ") -> " << std::endl;
	}

	pushOperation(AddOp());
	pushOperation(MultiplyOp());
	pushOperation(GreaterThanOp());
	pushOperation(LessThanOp());
	pushOperation(IntEqualsOp());

	printAllOperations();
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
	while(level < 2) {
		std::cout << std::endl << "LEVEL " << level << std::endl;
		for (auto it = allOperations.begin(); it != allOperations.end(); it++) {
			std::vector<Type> inputTypes = it->first;
			std::vector<Operation> operations = it->second;
			for (auto op : operations) {
				std::cout << "New Operation: " << op.printType() << std::endl;
				std::vector<Program*> children;
				// Push back first child program from level - 
				std::vector<Program> firstArgPrograms = getPrograms(inputTypes[0], level - 1);
				for (auto program_it = firstArgPrograms.begin(); program_it != firstArgPrograms.end(); program_it++) {
					children.push_back(&(*program_it));
					// Assume only 1 or 2 inputs at this time. Generalize later if possible
					if (inputTypes.size() == 2) {
						children.push_back(NULL);
						for (int anyLevel = 0; anyLevel < level; anyLevel++) {
							std::vector<Program> secondArgPrograms = getPrograms(inputTypes[1], anyLevel);
							for (auto program_it2 = secondArgPrograms.begin(); program_it2 != secondArgPrograms.end(); program_it2++) {
								children.at(1) = &(*program_it2);
								pushProgram(Program(op, children), level);
							}
						}
					}
					else if (inputTypes.size() > 2) {
						throw std::invalid_argument("Operators with > 2 args not currently accepted.");
					}
					else {
						pushProgram(Program(op, children), level);
					}
					children.clear();
				}
				std::cout << std::endl;
			}
		}
	 	level++;
	}

	return IntProgram(3);
}


template<typename ResT, typename ArgT>
std::vector<Program> Synthesizer<ResT, ArgT>::getPrograms(Type returnType, int level) {
	return allPrograms.at(returnType).at(level);
}


// Adds a program to the allPrograms map
template<typename ResT, typename ArgT>
void Synthesizer<ResT, ArgT>::pushProgram(Program p, int level) {
	std::cout << "Pushing program to Level " << level << ": " << p.toString() << " -- ";

	auto search = allPrograms.find(p.getType());
	if (search != allPrograms.end()) {
		//std::cout << "existing type... ";
		auto& vec = search->second;
		if (level > (vec.size() - 1)) {  // Check if this level has been created yet.
			//std::cout << "new level... ";
			if (level == vec.size()) {  // Check if this level is next empty spot in vector
				std::vector<Program> newVec;
				newVec.push_back(p);
				vec.push_back(newVec);
			} else throw std::invalid_argument("Trying to add program to level" + std::to_string(level));
		} else {
			std::cout << "existing level... ";
			vec.at(level).push_back(p);
		}
	} else {
		//std::cout << "new type! Thus new level";
		std::vector<std::vector<Program>> programsOfOneType;
		std::vector<Program> programsAtOneLevel;
		programsAtOneLevel.push_back(p);
		programsOfOneType.push_back(programsAtOneLevel);
		allPrograms.insert({p.getType(), programsOfOneType});
	}
	//std::cout << "evalulates to " << p.evaluate(inputs).toString();
	std::cout << std::endl;
}


// Adds an operation to the allOperations map
template<typename ResT, typename ArgT>
void Synthesizer<ResT, ArgT>::pushOperation(Operation op) {
	auto search = allOperations.find(op.argTypes);
	if (search != allOperations.end()) {
		auto& vec = search->second;
		vec.push_back(op);
	} else {
		std::vector<Operation> newVec;
		newVec.push_back(op);
		allOperations.insert({op.argTypes, newVec});
	}
}


template<typename ResT, typename ArgT>
void Synthesizer<ResT, ArgT>::printAllOperations() {
	std::cout << "Operations:" << std::endl;
	for (auto it = allOperations.begin(); it != allOperations.end(); it++) {
		std::cout << it->second.size();
		std::cout << " (";
		for (auto it2 = it->first.begin(); it2 != it->first.end(); it2++) {
			std::cout << TypeNames[static_cast<int>(*it2)];
			if (std::next(it2) != it->first.end()) std::cout << ", ";
		}
		std::cout << ") --> ANY ops" << std::endl;
		std::cout << "(";
		for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
			std::cout << it2->printType();
			if (std::next(it2) != it->second.end()) std::cout << ", ";
		}
		std::cout << ")" << std::endl;
	}
}
   

#endif
