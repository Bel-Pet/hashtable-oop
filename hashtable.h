#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

#include <iostream>
#include <string>
#include <list>
#include <algorithm>

typedef std::string Key;

struct Value {
    Value () = default;
    std::string name;
    unsigned age = 0;
    friend bool operator==(const Value& a, const Value& b) {
        if (a.age != b.age || a.name != b.name)
            return false;
        return true;
    }
    friend bool operator!=(const Value& a, const Value& b) {
        if (a == b)
            return false;
        return true;
    }
};

class HashTable {
public:
    HashTable();
    ~HashTable();
    HashTable(const HashTable& other);
    //Copy values from other HashTable
    HashTable& operator=(const HashTable& other);
    //Find the value, otherwise add new element with Key k and default Value
    Value& operator[](const Key& k);
    //Adds a new element, otherwise replaces the existing one
    bool insert(const Key& k, const Value& v);
    //Removes the element with key k and returns the success of the operation
    bool erase(const Key& k);
    //Returns search result
    [[nodiscard]] bool contains(const Key& k);
    //Find the value, otherwise print "No such element"
    Value& at(const Key& k);
    //Find the value, otherwise "No such element"
    [[nodiscard]] const Value& at(const Key& k) const;
    //Returns the number of items this HashTable
    [[nodiscard]] size_t size() const;
    //Checks if the table is empty
    [[nodiscard]] bool empty() const;
    //Clearing HashTable from items
    void clear();
    //Swap this HashTables with other
    void swap(HashTable& other);
    //Compares HashTables for each element
    friend bool operator==(const HashTable& a, const HashTable& b);
    //Compares HashTables for each element
    friend bool operator!=(const HashTable& a, const HashTable& b);
private:
    [[nodiscard]] Value& atValue(const Key& k) const;
    auto insert_value(const Key& k, const Value& v);
    std::list<std::pair<Key, Value>> **data_;
    size_t capacity_;
    size_t size_;
    [[nodiscard]] unsigned long hashFunction(const Key &k) const;
    void extension();
    static const size_t FIRST_TABLE_VOLUME = 4;
};

#endif //HASHTABLE_HASHTABLE_H
