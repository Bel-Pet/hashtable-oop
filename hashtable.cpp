#include "hashtable.h"

HashTable::HashTable(): data_(new std::list<std::pair<Key, Value>>* [HashTable::FIRST_TABLE_VOLUME]), capacity_(HashTable::FIRST_TABLE_VOLUME), size_(0) {
    for (int i = 0; i < capacity_; i++) {
        data_[i] = nullptr;
    }
}

HashTable::~HashTable() {
    delete[] data_;
}

HashTable::HashTable(const HashTable & other) : capacity_(other.capacity_), size_(other.size_), data_(new std::list<std::pair<Key, Value>>* [other.capacity_]) {
    for (int i = 0; i < capacity_; i++) {
        if (other.data_[i] != nullptr) {
            data_[i] = new std::list<std::pair<Key, Value>>;
            data_[i] = other.data_[i];
        }
    }
}

HashTable& HashTable::operator=(const HashTable & other) {
    if (&other != this) {
        for (int i = 0; i < capacity_; i++) {
            if (data_[i] != nullptr)
                delete data_[i];
        }
        delete[] data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        data_ = new std::list<std::pair<Key, Value>>* [capacity_];

        for (int i = 0; i < capacity_; i++) {
            data_[i] = new std::list<std::pair<Key, Value>>;
            data_[i] = other.data_[i];
        }
    }
    return *this;
}

Value& HashTable::operator[](Key &k) {
    auto it = data_[hashFunction(k)]->begin();

    std::pair<Key, Value> new_elem;
    new_elem.first = k;

    if (data_[hashFunction(k)] == nullptr) {
        data_[hashFunction(k)] = new std::list<std::pair<Key, Value>>;
        data_[hashFunction(k)]->push_back(new_elem);
        return it->second;
    }
    
    if (find(k, &it)) {
        return it->second;
    }

    data_[hashFunction(k)]->push_back(new_elem);

    return it->second;
}

bool HashTable::find(const Key &k, std::list<std::pair<Key, Value>>::iterator* it) const{
    while (*it != data_[hashFunction(k)]->end()) {
        if ((*it)->first == k)
            return true;
        (*it)++;
    }
    return false;
}

bool HashTable::insert(const Key& k, const Value& v) {
    if (size_ >= capacity_ * 3 / 4)
        extension();

    auto it = data_[hashFunction(k)]->begin();

    std::pair<Key, Value> new_elem;
    new_elem.first = k;
    new_elem.second = v;

    if (data_[hashFunction(k)] == nullptr) {
        data_[hashFunction(k)] = new std::list<std::pair<Key, Value>>;
        data_[hashFunction(k)]->push_back(new_elem);
        size_++;
        return true;
    }
    
    if (find(k, &it)) {
        it->second = v;
        return false;
    }

    data_[hashFunction(k)]->push_back(new_elem);
    size_++;

    return true;
}

bool HashTable::erase(const Key &k) {
    if (data_[hashFunction(k)] == nullptr)
        return false;
    
    auto it = data_[hashFunction(k)]->begin();

    if (find(k, &it)) {
        size_--;
        data_[hashFunction(k)]->erase(it);

        if (data_[hashFunction(k)]->empty())
            delete data_[hashFunction(k)];

        return true;
    }

    return false;
}

bool HashTable::contains(const Key& k) const {
    if (data_[hashFunction(k)])
        return false;
    
    auto it = data_[hashFunction(k)]->begin();
    return HashTable::find(k, &it);
}

Value& HashTable::at(const Key& k) {
    try {
        if (!contains(k)) throw std::runtime_error("No such element");
    } catch (std::runtime_error & e) {
        std::cout << e.what() << std::endl;
        auto it = data_[hashFunction(k)]->end();
        return it->second;
    }
    auto it = data_[hashFunction(k)]->begin();

    if (find(k, &it)) {
        return it->second;
    }
}

const Value& HashTable::at(const Key &k) const {
    try {
        if (!contains(k)) throw std::runtime_error("No such element");
    } catch (std::runtime_error & e) {
        std::cout << e.what() << std::endl;
        auto it = data_[hashFunction(k)]->end();
        return it->second;
    }
    auto it = data_[hashFunction(k)]->begin();

    if (find(k, &it))
        return const_cast<Value&> (it->second);
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
    for (int i = 0; i < capacity_; i++) {
        if (data_[i] != nullptr)
            delete data_[i];
    }
    delete[] data_;
    data_ = new std::list<std::pair<Key, Value>>* [FIRST_TABLE_VOLUME];
    capacity_ = FIRST_TABLE_VOLUME;
    size_ = 0;

    for (int i = 0; i < capacity_; i++) {
        data_[i] = nullptr;
    }
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
    auto other = new std::list<std::pair<Key, Value>>* [capacity_ * 2];
    for (int i = 0; i < (capacity_*2); i++) {
        other[i] = nullptr;
    }
    std::swap(other, data_);
    size_t other_capacity = capacity_;
    capacity_ *= 2;

    for (int i = 0; i < other_capacity; i++)
        if(other[i] != nullptr) {
            auto it = other[i]->begin();
            while (it != other[i]->end()) {
                if (data_[hashFunction(it->first)] == nullptr)
                    data_[hashFunction(it->first)] = new std::list<std::pair<Key, Value>>;

                data_[hashFunction(it->first)]->push_back(*it);
                it++;
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
                if (!b.contains(it_a->first))
                    return false;
                if (it_a->second != b.at(it_a->first))
                    return false;
            }
        }
    }
    return true;
}

bool operator!=(const HashTable& a, const HashTable& b) {
    return !(a == b);
}
