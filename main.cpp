#include <iostream>

#include <boost/any.hpp>

#include "Synthesizer.h"
#include "utils/util.h"

int main (int argc, char *argv[]) {
    Synthesizer<bool, int> s;

    // first sample
    // input
	std::vector<boost::any> v;
    v.push_back(boost::any(3));
    v.push_back(boost::any(14));
    // output
    List l1;
    l1.addToList(17);
    l1.addToList(42);

    // second sample
    // input
    std::vector<boost::any> v2;
    v2.push_back(boost::any(3));
    v2.push_back(boost::any(15));
    // output
    List l2;
    l2.addToList(18);
    l2.addToList(45);

    // third sample
    // input
    std::vector<boost::any> v3;
    v3.push_back(boost::any(3));
    v3.push_back(boost::any(25));
    // output
    List l3;
    l3.addToList(28);
    l3.addToList(75);

	std::vector<std::pair<std::vector<boost::any>, boost::any>> samples;
	samples.push_back({v, boost::any(l1)});
	samples.push_back({v2, boost::any(l2)});
	samples.push_back({v3, boost::any(l3)});

	auto p = s.findFittingProgram(samples);

    std::cout << "This is the one! : Program: " << p.printId() << std::endl;
    std::cout << "f(...) = " << p.toString() << std::endl;

    // print stuff out
    for (auto sample : samples) {
        auto input = sample.first;
        auto exp_output = sample.second;

        std::cout << "f(";
        for (auto val = input.begin(); val!= input.end(); val++) {
            std::cout << utils::toString(*val);
            if (std::next(val,1) != input.end())
                std::cout << ",";
        }
        std::cout << ") = " << utils::toString(p.evaluate(input));
        std::cout << " [expected output is " << utils::toString(exp_output) << "]" << std::endl;
    }

    std::cout << "Goodbye from main." << std::endl;
}

