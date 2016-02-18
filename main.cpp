#include <iostream>

#include "Synthesizer.h"

int main (int argc, char *argv[]) { 

	std::cout << "Hello from main." << std::endl;
	Synthesizer<int, int> s;
	std::cout << "Goodbye from main." << std::endl;
}

