#include <iostream>

#include <boost/any.hpp>

#include "Synthesizer.h"
#include "utils/util.h"

std::vector<std::pair<std::vector<boost::any>, boost::any>> testData1() {
    std::vector<boost::any> v;
    v.push_back(boost::any(3));
    v.push_back(boost::any(4));
    List l1;
    l1.addToList(7);
    l1.addToList(12);

    std::vector<boost::any> v2;
    v2.push_back(boost::any(8));
    v2.push_back(boost::any(2));
    List l2;
    l2.addToList(10);
    l2.addToList(16);

    std::vector<boost::any> v3;
    v3.push_back(boost::any(-5));
    v3.push_back(boost::any(3));
    List l3;
    l3.addToList(-2);
    l3.addToList(-15);

    std::vector<std::pair<std::vector<boost::any>, boost::any>> samples;
    samples.push_back({v, boost::any(21)});
    samples.push_back({v2, boost::any(80)});
    samples.push_back({v3, boost::any(10)});

    return samples;
};

std::vector<std::pair<std::vector<boost::any>, boost::any>> testData2() {
    std::vector<boost::any> v;
    v.push_back(boost::any(3));
    v.push_back(boost::any(4));
    List l1;
    l1.addToList(7);
    l1.addToList(12);

    std::vector<boost::any> v2;
    v2.push_back(boost::any(8));
    v2.push_back(boost::any(2));
    List l2;
    l2.addToList(10);
    l2.addToList(16);

    std::vector<boost::any> v3;
    v3.push_back(boost::any(-5));
    v3.push_back(boost::any(3));
    List l3;
    l3.addToList(-2);
    l3.addToList(-15);

    std::vector<std::pair<std::vector<boost::any>, boost::any>> samples;
    samples.push_back({v, boost::any(l1)});
    samples.push_back({v2, boost::any(l2)});
    samples.push_back({v3, boost::any(l3)});

    return samples;
};

int main (int argc, char *argv[]) {
    Synthesizer s;

    auto samples = testData2();
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
}

