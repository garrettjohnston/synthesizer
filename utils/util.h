#ifndef __PIE_UTILS_H__
#define __PIE_UTILS_H__

#include <boost/any.hpp>
#include "../userDefinedTypes/List.hpp"

namespace utils {
    std::string toString(boost::any val) {
        try {
            int i = boost::any_cast<int>(val);
            return std::to_string(i);
        } catch (boost::bad_any_cast e) { }
        try {
            bool b = boost::any_cast<bool>(val);
            return b ? "true" : "false";
        } catch (boost::bad_any_cast e) { }
        try {
            std::string s = boost::any_cast<std::string>(val);
            return s;
        } catch (boost::bad_any_cast e) { }
        try {
            List l = boost::any_cast<List>(val);
            return l.toString();
        } catch (boost::bad_any_cast e) {
            return "unknown type";
        }
    };

}


#endif