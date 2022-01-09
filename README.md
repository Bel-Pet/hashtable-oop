# Реализовать хэш таблицу на основе заданного интерфейса. Алгоритм разрешения коллизий оставляется на усмотрение студента.

Требования:

Код должен быть покрыт тестами https://github.com/google/googletest
Публичные методы должны быть документированы (на английском)
Программа должна собираться с помощью cmake
Хэш функцию написать самостоятельно (не использовать std::hash)
В программе не должно быть утечек памяти

Интерфейс:

typedef std::string Key;

struct Value {
   Value (std::string n, unsigned a = 0) : name(n), age(a) {}
   std::string name;
   unsigned age;
};

class HashTable {
public:
   HashTable();
   ~HashTable();

   HashTable& operator=(const HashTable& b);

   HashTable(const HashTable& b);

   void swap(HashTable& b);

   void clear();

   bool erase(const Key& k);

   bool insert(const Key& k, const Value& v);

   bool contains(const Key& k) const;
  
   Value& operator[](const Key& k);

   Value& at(const Key& k);
   const Value& at(const Key& k) const;
  
   size_t size() const;

   bool empty() const;

   friend bool operator==(const HashTable& a, const HashTable& b);
   friend bool operator!=(const HashTable& a, const HashTable& b);
};

Полезные ссылки

https://en.cppreference.com/w/
https://www.valgrind.org/
https://google.github.io/googletest/quickstart-cmake.html
https://developer.apple.com/library/archive/documentation/Performance/Conceptual/ManagingMemory/Articles/FindingLeaks.html
