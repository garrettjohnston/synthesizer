#ifndef __PIE_VALUE_H__
#define __PIE_VALUE_H__

#include <string>

#include "../Type.h"
#include <boost/any.hpp>

class Value : public boost::any {
public:
	Value(): boost::any() {};
	Value(const boost::any &a): boost::any(a) {}
	std::string toString() {
		try {
			int i = boost::any_cast<int>(*this);
			return std::to_string(i);
		} catch(boost::bad_any_cast e) { }
		try {
			bool b = boost::any_cast<bool>(*this);
			return b ? "true" : "false";
		} catch(boost::bad_any_cast e) { }
		try {
			std::string s = boost::any_cast<std::string>(*this);
			return s;
		} catch(boost::bad_any_cast e) {
			return "unknown type"; 
		}
	};
};

#endif
