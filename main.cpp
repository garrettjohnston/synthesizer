#include <iostream>

#include <boost/any.hpp>

#include "Synthesizer.h"

int main (int argc, char *argv[]) { 

    Synthesizer<bool, int, bool> s;

    // first sample
	std::vector<boost::any> v;
    v.push_back(boost::any(3));
    v.push_back(boost::any(10));
    v.push_back(boost::any(true));

    // second sample
    std::vector<boost::any> v2;
    v2.push_back(boost::any(3));
    v2.push_back(boost::any(11));
    v2.push_back(boost::any(true));

	std::vector<std::pair<std::vector<boost::any>, boost::any>> samples;
	samples.push_back({v, boost::any(true)});
	samples.push_back({v2, boost::any(false)});

	auto p = s.findFittingProgram(samples);

    std::cout << "This is the one! : Program: " << p.printId() << " -- " << p.toString();
    std::cout << " evaluates to " << utils::toString(p.evaluate(v)) << std::endl;

    std::cout << "Goodbye from main." << std::endl;
}

