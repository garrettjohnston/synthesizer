#ifndef SYNTHESIZER_LIST_HPP
#define SYNTHESIZER_LIST_HPP

#include <vector>
#include "../Type.h"

class List {
public:
    List() { }
    void addToList(int val) { list.push_back(val); }
    int size() const { return list.size(); }
    std::vector<int> getList() const { return list; }
    bool operator==(const List& l2);
    std::string toString();
private:
    std::vector<int> list;

};

bool List::operator==(const List& l2) {
    if (this->size() != l2.size()) {
        return false;
    }

    std::vector<int> list1 = this->getList();
    std::vector<int> list2 = l2.getList();

    for (int i = 0; i < this->size(); i++) {
        if (list1[i] != list2[i]) {
            return false;
        }
    }
    return true;
}

std::string List::toString() {
    std::string s = "[";
    for (auto item = list.begin(); item != list.end(); item++) {
        s += std::to_string(*item);
        s += std::next(item, 1) == list.end() ? "" : ",";
    }
    s += "]";
    return s;
}

#endif