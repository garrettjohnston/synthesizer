#include <iostream>

#include "Synthesizer.h"

int main (int argc, char *argv[]) { 

	Synthesizer<int, int> s;
	auto var = s.findNewFeature();
	std::cout << "Goodbye from main." << std::endl;
}

