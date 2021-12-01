#include "hashtable.h"

HashTable::HashTable(): data_(new std::list<std::pair<Key, Value>> [FIRST_TABLE_VOLUME]), capacity_(FIRST_TABLE_VOLUME) {}

HashTable::~HashTable() {
    delete[] data_;
}

HashTable::HashTable(const HashTable & other) : capacity_(other.capacity_), size_(other.size_), data_(new std::list<std::pair<Key, Value>> [other.capacity_]) {
    for (int i = 0; i < capacity_; i++)
        data_[i] = other.data_[i];
}

HashTable& HashTable::operator=(const HashTable & other) {
    if (&other != this) {
        delete[] data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        data_ = new std::list<std::pair<Key, Value>> [capacity_];

        for (int i = 0; i < capacity_; i++)
            data_[i] = other.data_[i];
    }
    return *this;
}

Value& HashTable::operator[](Key &k) {
//    try {
//        if (k.empty()) throw std::runtime_error("Empty key");
//    } catch (std::runtime_error & e) {
//        std::cout << e.what() << std::endl;
//        auto it = data_[hashFunction(k)].end();
//        return it->second;
//    }
    auto it = data_[hashFunction(k)].begin();

    while (it != data_[hashFunction(k)].end()) {
        if (it->first == k) return it->second;
        it++;
    }
    std::pair<Key, Value> new_elem;
    new_elem.first = k;
    // use lambda?
    data_[hashFunction(k)].push_back(new_elem);
    return it->second;
}

bool HashTable::insert(const Key& k, const Value& v) {

    if (size_ >= capacity_ * 3 / 4)
        extension();

    auto it = data_[hashFunction(k)].begin();

    while (it != data_[hashFunction(k)].end()) {
        if (it->first == k) {
            it->second = v;
            return false;
        }
        it++;
    }
    data_[hashFunction(k)].push_back({k, v});
    size_++;
    return true;
}

bool HashTable::erase(const Key &k) {
    auto it = data_[hashFunction(k)].begin();

    while (it != data_[hashFunction(k)].end()) {
        if (it->first == k) {
            size_--;
            data_[hashFunction(k)].erase(it);
            return true;
        }
        it++;
    }
    return false;
}

bool HashTable::contains(const Key& k) const {
    auto it = data_[hashFunction(k)].begin();

    return find(k, it);
}

bool
HashTable::find(const Key &k, std::list<std::pair<Key, Value>, std::allocator<std::pair<Key, Value>>>::iterator &it) {
    while (it != data_[hashFunction(k)].end()) {
        if (it->first == k)
            return true;
        it++;
    }
    return false;
}

Value& HashTable::at(const Key& k) {
    try {
        if (!contains(k)) throw std::runtime_error("No such element");
    } catch (std::runtime_error & e) {
        std::cout << e.what() << std::endl;
        auto it = data_[hashFunction(k)].end();
        return it->second;
    }
    auto it = data_[hashFunction(k)].begin();

    while (it != data_[hashFunction(k)].end()) {
        if (it->first == k)
            return it->second;
        it++;
    }
    std::pair<Key, Value> new_elem;
    new_elem.first = k;
    data_[hashFunction(k)].push_back(new_elem);
    return it->second;
}

Value& HashTable::at(const Key &k) const {
    try {
        if (!contains(k)) throw std::runtime_error("No such element");
    } catch (std::runtime_error & e) {
        std::cout << e.what() << std::endl;
        auto it = data_[hashFunction(k)].end();
        return it->second;
    }
    auto it = data_[hashFunction(k)].begin();

    while (it != data_[hashFunction(k)].end()) {
        if (it->first == k)
            return it->second;
        it++;
    }
    std::pair<Key, Value> new_elem;
    new_elem.first = k;
    data_[hashFunction(k)].push_back(new_elem);
    return it->second;
}

size_t HashTable::size() const {
    return size_;
}

bool HashTable::empty() const {
    if (size_ == 0)
        return true;
    return false;
}

void HashTable::clear() {
    delete[] data_;
    data_ = new std::list<std::pair<Key, Value>> [FIRST_TABLE_VOLUME];
    capacity_ = FIRST_TABLE_VOLUME;
    size_ = 0;
}

void HashTable::swap(HashTable &other) {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

unsigned long HashTable::hashFunction(const Key &k) const {
    unsigned long hash = 0;
    int value = 13;

    for(char i : k) {
        hash = hash + ((int)i * value) % capacity_;
        value *= value;
    }
    return hash;
}

void HashTable::extension() {
    auto other = new std::list<std::pair<Key, Value>> [capacity_ * 2];
    std::swap(other, data_);
    size_t other_capacity = capacity_;
    // update capacity, add test

    for (int i = 0; i < other_capacity; i++)
        if(!other[i].empty()) {
            auto it = other[i].begin();
            while (it != other[i].end()) {
                data_[hashFunction(it->first)].push_back(*it);
                it++;
            }
        }
    }
    delete[] other;
}

bool operator==(const HashTable& a, const HashTable& b) {
    if (a.size() != b.size())
        return false;
    for (size_t i = 0; i < a.capacity_; i++) {
        if (a.data_[i].size() != b.data_[i].size())
            return false;
        auto it_a = a.data_[i].begin();
        if (!a.data_[i].empty()) {
            if (!b.contains(it_a->first))
                return false;
            if (it_a->second != b.at(it_a->first))
                return false;
        }
    }
    return true;
}

bool operator!=(const HashTable& a, const HashTable& b) {
    if (a == b)
        return false;
    return true;
}