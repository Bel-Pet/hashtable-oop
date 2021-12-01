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
    HashTable(const HashTable& other); //+

    HashTable& operator=(const HashTable& other); //+

    Value& operator[]( Key& k); //+

    bool insert(const Key& k, const Value& v); //+

    bool erase(const Key& k); //+

    [[nodiscard]] bool contains(const Key& k) const; //+

    Value& at(const Key& k);

    [[nodiscard]] Value& at(const Key& k) const;

    [[nodiscard]] size_t size() const; //+

    [[nodiscard]] bool empty() const; //+

    void clear(); //+

    void swap(HashTable& other); //+

    friend bool operator==(const HashTable& a, const HashTable& b); //+
    friend bool operator!=(const HashTable& a, const HashTable& b); //+
private:
    const size_t FIRST_TABLE_VOLUME = 1;
    auto find(const Key& k);
    // * -> **
    std::list<std::pair<Key, Value>> *data_;
    size_t capacity_;
    size_t size_ = 0;
    [[nodiscard]] unsigned long hashFunction(const Key &k) const;
    void extension();

    bool find(const Key &k, std::list<std::pair<Key, Value>, std::allocator<std::pair<Key, Value>>>::iterator &it);
};

#endif //HASHTABLE_HASHTABLE_H
