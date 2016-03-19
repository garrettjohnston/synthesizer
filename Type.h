#ifndef __PIE_TYPE_H__
#define __PIE_TYPE_H__

#include <stdexcept>
#include <boost/any.hpp>
#include "userDefinedTypes/List.hpp"
#include <utility>


// TODO: Ideally, put all these special functions in some "Type" namespace without screwing everything else up

enum class Type { TInt, TBool, TStr, TList };

static std::string TypeNames[] { "Int", "Bool", "Str", "List" };

// Add any primitives you want in here!
static std::vector<std::pair<Type, std::vector<boost::any>>> primitives {
        { std::make_pair<Type, std::vector<boost::any>>(Type::TInt, {0, 1}) },
        { std::make_pair<Type, std::vector<boost::any>>(Type::TBool, {true, false}) },
        { std::make_pair<Type, std::vector<boost::any>>(Type::TStr, {std::string("")}) },
        { std::make_pair<Type, std::vector<boost::any>>(Type::TList, {List()}) }
};

// Annoying and ugly function, but it is necessary to get around c++ template/type issues.
Type getTypeOfAny(boost::any val) {
    try {
        int i = boost::any_cast<int>(val);
        return Type::TInt;
    } catch (boost::bad_any_cast e) { }

    try {
        bool b = boost::any_cast<bool>(val);
        return Type::TBool;
    } catch (boost::bad_any_cast e) { }

    try {
        std::string s = boost::any_cast<std::string>(val);
        return Type::TStr;
    } catch (boost::bad_any_cast e) { }

    try {
        List l = boost::any_cast<List>(val);
        return Type::TList;
    } catch (boost::bad_any_cast e) {
        throw std::invalid_argument("boost::any value did not match any types");
    }
};

// Best way to check for boost::any value equality
bool isEqual(boost::any func_out, boost::any exp_out, Type type) {
    switch (type) {
        case Type::TInt:
            return boost::any_cast<int>(func_out) == boost::any_cast<int>(exp_out);

        case Type::TBool:
            return boost::any_cast<bool>(func_out) == boost::any_cast<bool>(exp_out);

        case Type::TStr: {
            std::string str1 = boost::any_cast<std::string>(func_out);
            std::string str2 = boost::any_cast<std::string>(exp_out);
            return str1.compare(str2) == 0;
        }

        case Type::TList: {
            return boost::any_cast<List>(func_out) == boost::any_cast<List>(exp_out);
        }
//        default:
//            throw std::invalid_argument("Type could not be matched");
    }
}

#endif
