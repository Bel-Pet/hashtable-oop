#include "hashtable.h"

HashTable::HashTable(): data_(new std::list<std::pair<Key, Value>>* [HashTable::FIRST_TABLE_VOLUME]()), capacity_(HashTable::FIRST_TABLE_VOLUME), size_(0) {}

HashTable::~HashTable() {
    for (int i = 0; i < capacity_; i++) {
        if (data_[i] != nullptr)
            delete data_[i];
    }
    delete[] data_;
}

HashTable::HashTable(const HashTable & other) : capacity_(other.capacity_), size_(other.size_), data_(new std::list<std::pair<Key, Value>>* [other.capacity_]()) {
    for (int i = 0; i < capacity_; i++) {
        if (other.data_[i] != nullptr) {
            data_[i] = new std::list<std::pair<Key, Value>>;
            auto it = other.data_[i]->begin();
            while (it != other.data_[i]->end()) {
                data_[i]->push_back(*it);
                it++;
            }
        }
    }
}

HashTable& HashTable::operator=(const HashTable & other) {
    if (&other != this) {
        HashTable result(other);
        swap(result);
    }
    return *this;
}

auto HashTable::find(const Key &k) const {
    auto it = data_[hashFunction(k)]->begin();
    while (it != data_[hashFunction(k)]->end()) {
        if (it->first == k)
            return it;
        it++;
    }
    return it;
}

// CR: check that works correctly
const auto HashTable::insert_value(const Key& k, const Value& v) {
    if (size_ >= capacity_ * 3 / 4) extension();

    if (data_[hashFunction(k)] == nullptr)
        data_[hashFunction(k)] = new std::list<std::pair<Key, Value>>;

    auto it = find(k);
    if (it == data_[hashFunction(k)]->end()) {
        data_[hashFunction(k)]->push_back({k, v});
        return --it;
    }
    return it;
}


bool HashTable::insert(const Key& k, const Value& v) {
    auto it = insert_value(k, v);
    if (it->second != v) {
        it->second = v;
        return false;
    }
    return true;
}
bool HashTable::erase(const Key &k) {
    if (size_ == 0 || data_[hashFunction(k)] == nullptr)
        return false;
    auto it = find(k);
    if (it != data_[hashFunction(k)]->end()) {
        size_--;
        data_[hashFunction(k)]->erase(it);
        return true;
    }
    return false;
}

bool HashTable::contains(const Key& k) {
    if (data_[hashFunction(k)] == nullptr)
        return false;

    auto it = find(k);
    return it != data_[hashFunction(k)]->end();
}

size_t HashTable::size() const {
    return size_;
}

bool HashTable::empty() const {
    return size_ == 0;
}

// CR: check that works correctly
void HashTable::clear() {
    for (int i = 0; i < capacity_; i++) {
        if (data_[i] != nullptr)
            delete data_[i];
    }
    size_ = 0;
//    HashTable newHashTable;
//    swap(newHashTable);
}

void HashTable::swap(HashTable &other) {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

Value& HashTable::operator[](const Key &k) {
    const Value & v = Value();
    auto it = insert_value(k, v);
    return it->second;
}

Value& HashTable::at(const Key& k) {
    if (data_[hashFunction(k)] == nullptr)
        data_[hashFunction(k)] = new std::list<std::pair<Key, Value>>;
    auto it = find(k);
    if (it == data_[hashFunction(k)]->end()) throw std::runtime_error("No such element");
    return it->second;
}

const Value& HashTable::at(const Key &k) const{
    // CR: separate const_at
    if (data_[hashFunction(k)] == nullptr)
        data_[hashFunction(k)] = new std::list<std::pair<Key, Value>>;
    auto it = find(k);
    if (it == data_[hashFunction(k)]->end()) throw std::runtime_error("No such element");
    return const_cast<Value&>(it->second);
}

unsigned long HashTable::hashFunction(const Key &k) const {
    unsigned long hash = 0;
    int value = 31;

    for(char i : k) {
        hash = hash + ((int)i * value) % capacity_;
        value *= value;
    }
    return hash;
}


void HashTable::extension() {
    auto other = new std::list<std::pair<Key, Value>>* [capacity_ * 2]();
    std::swap(other, data_);
    size_t other_capacity = capacity_;
    capacity_ *= 2;
    size_t amountOfElement = size_;

    for (int i = 0; i < other_capacity && amountOfElement != 0; i++) {
        if(other[i] != nullptr) {
            auto it = other[i]->begin();
            while (it != other[i]->end()) {
                if (data_[hashFunction(it->first)] == nullptr)
                    data_[hashFunction(it->first)] = new std::list<std::pair<Key, Value>>;
                data_[hashFunction(it->first)]->push_back(*it);
                amountOfElement--;
                it++;
            }
        }
    }

    for (int i = 0; i < other_capacity; i++) {
        if (other[i] != nullptr)
            delete other[i];
    }
    delete[] other;
}

bool operator==(const HashTable& a, const HashTable& b) {
    if (a.size() != b.size())
        return false;

    for (size_t i = 0; i < a.capacity_; i++) {
        if (a.data_[i] != nullptr) {
            auto it_a = a.data_[i]->begin();

            while (it_a != a.data_[i]->end()) {
                if (b.data_[b.hashFunction(it_a->first)] == nullptr)
                    return false;

                auto it_b = b.find(it_a->first);

                if (it_b == b.data_[b.hashFunction(it_a->first)]->end())
                    return false;

                if (it_b->second != it_a->second)
                    return false;

                it_a++;
            }
        }
    }
    return true;
}

bool operator!=(const HashTable& a, const HashTable& b) {
    return !(a == b);
}
