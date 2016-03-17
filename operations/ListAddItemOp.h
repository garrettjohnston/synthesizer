#ifndef SYNTHESIZER_LISTADDITEMOP_H_H
#define SYNTHESIZER_LISTADDITEMOP_H_H

#include <functional>
#include <vector>
#include <string>
#include <stdexcept>
#include <boost/any.hpp>
#include <typeinfo>
#include <iostream>

#include "Operation.h"
#include "IdentityOp.h"
#include "../Type.h"
#include "../userDefinedTypes/List.hpp"

class ListAddItemOp: public Operation {
public:
    ListAddItemOp() {
        f = [](std::vector<boost::any> args) {
            if (args.size() != 2) {
                throw std::invalid_argument("ListAddItemOp requires 2 args but was given " + std::to_string(args.size()));
            } else {
                List arg1 = boost::any_cast<List>(args[0]);
                int arg2 = boost::any_cast<int>(args[1]);
                arg1.addToList(arg2);

                return boost::any(arg1);
            }
        };

        retType = Type::TList;
        argTypes.push_back(Type::TList);
        argTypes.push_back(Type::TInt);
        isSymmetric = false;
        isComposable = false;
    }

    std::string toString(std::vector<std::tuple<Type, int, int>> args) {
        if (args.size() != 2) {
            return "BAD_LIST_ADD_ITEM";
        }
        return "(" + programContainer->get(args[0]).toString() + ".append(" + programContainer->get(args[1]).toString() + "))";
    }

    std::string name() {
        return "ListAddItemOp";
    }

    bool areGoodArgs(std::vector<std::tuple<Type, int, int>> program) {
        return true;
    }

    bool isRedundant(std::vector<std::tuple<Type, int, int>> p1, std::vector<std::tuple<Type, int, int>> p2) {
        return false;
    }
};

#endif
