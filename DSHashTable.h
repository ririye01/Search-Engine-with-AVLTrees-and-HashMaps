#include <vector>
#include <list>
#include <forward_list>
#include <utility>
#include <functional>


#include<iostream>

using namespace std;

using namespace std;

template <typename Key, typename Value>
class DSHashTable
{
private:
    vector<forward_list<pair<Key, Value>>> table;
    hash<Key> hasher;

public:
    // default constructor
    explicit DSHashTable(size_t size = 101)
    {
        table.resize(size);
    }

    // needs a copy constructor, assignment etc.

    bool insert(const Key &x, const Value &y)
    {
        pair<Key, Value> myPair;
        myPair.first = x;
        myPair.second = y;
        auto &whichEntry = table[calcHash(x)];
        whichEntry.push_front(myPair);
        return true;
    }

    Value get(const Key &x) {
        auto &whichEntry = table[calcHash(x)];

        if (whichEntry.empty()) {
            throw std::runtime_error("No value for the provided key");
        }

        for (auto const &i : whichEntry) {
            if (x == i.first) { return i.second; }
        }
        throw std::runtime_error("Value does not exist!");
    }


    void remove(const Key &x)
    {
        auto &whichEntry = table[calcHash(x)];

        for (auto &i: whichEntry) {
            if (i.first == x) {
                whichEntry.remove(i);
                return;
            }
        }

        throw std::runtime_error("Key does not exist!");

    }

    void print() {
        for (auto const &i : table) {
            for (auto const &j : i) {
                cout << " Key: " << j.first << " Value: " << j.second << endl;
            }
        }
    }

    bool contains(const Key &x) const
    {
        auto &whichEntry = table[calcHash(x)];
        for (auto const &i: whichEntry) {
            if (i.first == x) {
                return true;
            }
        }

        return false;


    }


    void makeEmpty()
    {
        table.clear();
    }

    int size() {
        int size = 0;

        for (int i = 0; i < table.size(); ++i) {
            size += table[i].size();
        }

        return size;
    }

    bool isEmpty() {

        if (size() == 0) { return true; }
        return false;
    }

    // size, get keys, iterator, etc. are missing

private:
    size_t calcHash(const Key &x) const
    {
        return hasher(x) % table.size();
    }
};

#ifndef ASSIGNMENT_4_OFFLINE_DSHASHTABLE_H
#define ASSIGNMENT_4_OFFLINE_DSHASHTABLE_H

#endif //ASSIGNMENT_4_OFFLINE_DSHASHTABLE_H
