#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

#include <iostream>
#include <string>
#include <list>

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

    HashTable& operator=(const HashTable& other); //Copy values from other HashTable

    Value& operator[]( Key& k); //Find the value, otherwise add pair<Key, Value>

    bool insert(const Key& k, const Value& v); //Add pair<Key, Value>, otherwise change the value

    bool erase(const Key& k); //Delete pair<Key, Value>

    [[nodiscard]] bool contains(const Key& k) const; //Find Value

    Value& at(const Key& k); //Find the value, otherwise "No such element"

    [[nodiscard]] const Value& at(const Key& k) const; //Find the value, otherwise "No such element"

    [[nodiscard]] size_t size() const; //Number of values in HashTable

    [[nodiscard]] bool empty() const; //

    void clear(); //Clearing HashTable from values

    void swap(HashTable& other); //Swap HashTables

    friend bool operator==(const HashTable& a, const HashTable& b);
    friend bool operator!=(const HashTable& a, const HashTable& b);
private:
    std::list<std::pair<Key, Value>> **data_;
    size_t capacity_;
    size_t size_;
    [[nodiscard]] unsigned long hashFunction(const Key &k) const;
    void extension();
    static const size_t FIRST_TABLE_VOLUME = 1;
    bool find(const Key& k, std::list<std::pair<Key, Value>>::iterator* it) const;
};

#endif //HASHTABLE_HASHTABLE_H
