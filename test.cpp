#include <gtest/gtest.h>
#include "hashtable.h"

TEST(hashtable, CorrectWorkOperatorEqualsAndNotEquals) {
HashTable a;
Value elem1 = {"Eric", 13};
Value elem2 = {"Erlo", 42};
Value elem3 = {"Avgust", 33};
Value elem4 = {"Jfwkesf", 134};

a.insert("a", elem1);
a.insert("b", elem2);
a.insert("c", elem3);
a.insert("d", elem4);

HashTable b;
b.insert("d", elem4);
b.insert("c", elem3);
b.insert("b", elem2);
b.insert("a", elem1);

bool result1 = a == b;
bool result2 = a != b;

EXPECT_TRUE(result1);
EXPECT_TRUE(!result2);

a.insert("e", elem1);
b.insert("e", elem2);

result1 = a == b;
result2 = a != b;

EXPECT_TRUE(!result1);
EXPECT_TRUE(result2);

a.erase("e");
b.erase("e");

EXPECT_TRUE(result1);
EXPECT_TRUE(!result2);
}

TEST(hashtable, OperatorSquareBracketsWhenElementExisted) {
HashTable a;
Value elem3 = {"Avgust", 33};

a.insert("fds", elem3);

Value result = a.operator[]("fds");

EXPECT_EQ(result.name, elem3.name);
EXPECT_EQ(result.age, elem3.age);
}

TEST(hashtable, OperatorSquareBracketsWhenElementNotExisted) {
HashTable a;
Value elem1 = {"Eric", 13};
Value elem2 = {"Erlo", 42};

a.insert("jksd", elem1);
a.insert("sdfn", elem2);

Value result = a.operator[]("fds");

EXPECT_EQ(result.name.empty(), true);
EXPECT_EQ(result.age, 0);
}

TEST(hashtable, CorrectWorkCopyConstructor) {
HashTable a;
Value elem1 = {"Eric", 13};
Value elem2 = {"Erlo", 42};
Value elem3 = {"Avgust", 33};

a.insert(elem1.name, elem1);
a.insert(elem2.name, elem2);
a.insert(elem3.name, elem3);

HashTable b(a);

EXPECT_EQ(b.size(), 3);
EXPECT_TRUE(b.contains(elem1.name));
EXPECT_TRUE(b.contains(elem2.name));
EXPECT_TRUE(b.contains(elem3.name));
}

TEST(hashtable, CorrectWorkOperatorAssignmentConstructor) {
HashTable a;
Value elem1 = {"Eric", 13};
Value elem2 = {"Erlo", 42};
Value elem3 = {"Avgust", 33};

a.insert(elem1.name, elem1);
a.insert(elem2.name, elem2);
a.insert(elem3.name, elem3);

HashTable b(a);
Value elem4 = {"Jfwkesf", 134};
Value elem5 = {"Gedds", 4234};

b.insert(elem4.name, elem4);
b.insert(elem5.name, elem5);

b = a;

EXPECT_EQ(b.size(), 3);
EXPECT_TRUE(b.contains(elem1.name));
EXPECT_TRUE(b.contains(elem2.name));
EXPECT_TRUE(b.contains(elem3.name));
EXPECT_TRUE(!(b.contains(elem4.name)));
EXPECT_TRUE(!(b.contains(elem5.name)));
}

TEST(hashtable, CorrectContains) {
HashTable a;
Value elem1 = {"Eric", 13};
Value elem2 = {"Erlo", 42};
Value elem3 = {"Avgust", 33};

a.insert(elem1.name, elem1);
a.insert(elem2.name, elem2);
a.insert(elem3.name, elem3);

EXPECT_EQ(a.contains(elem3.name), true);
}

TEST(hashtable, EmptyForEmptyHashTable) {
HashTable a;
EXPECT_TRUE(a.empty());
}

TEST(hashtable, EmptyForNotEmptyHashTable) {
HashTable a;
Value elem1 = {"Eric", 13};
Value elem2 = {"Erlo", 42};
Value elem3 = {"Avgust", 33};

a.insert(elem1.name, elem1);
a.insert(elem2.name, elem2);
a.insert(elem3.name, elem3);

EXPECT_TRUE(!(a.empty()));
}

TEST(hashtable, SizeIsZeroForEmpty) {
    HashTable a;
    EXPECT_EQ(a.size(), 0);
}

TEST(hashtable, SizeIsNotEmpty) {
HashTable a;
Value elem1 = {"Eric", 13};
Value elem2 = {"Erlo", 42};
Value elem3 = {"Avgust", 33};

a.insert(elem1.name, elem1);
a.insert(elem2.name, elem2);
a.insert(elem3.name, elem3);

EXPECT_EQ(a.size(), 3);
}

TEST(hashtable, SwapCorrect) {
HashTable a;
Value elem1 = {"Eric", 13};
Value elem2 = {"Erlo", 42};
Value elem3 = {"Avgust", 33};

a.insert(elem1.name, elem1);
a.insert(elem2.name, elem2);
a.insert(elem3.name, elem3);

HashTable b;
b.insert(elem1.name, elem1);
b.insert(elem2.name, elem2);

a.swap(b);

EXPECT_EQ(a.size(), 2);
EXPECT_EQ(b.size(), 3);
}

TEST(hashtable, ClearCorrectForNotEmptyHashTable) {
HashTable a;
Value elem1 = {"Eric", 13};
Value elem2 = {"Erlo", 42};
Value elem3 = {"Avgust", 33};

a.insert(elem1.name, elem1);
a.insert(elem2.name, elem2);
a.insert(elem3.name, elem3);

a.clear();

EXPECT_EQ(a.size(), 0);
}

TEST(hashtable, ClearCorrectForEmptyHashTable) {
HashTable a;
Value elem1 = {"Eric", 13};
Value elem2 = {"Erlo", 42};
Value elem3 = {"Avgust", 33};

a.clear();

EXPECT_EQ(a.size(), 0);
}

TEST(hashtable, EraseCorrectForNotEmptyHashTable) {
HashTable b;
Value elem1 = {"Eric", 13};
Value elem2 = {"Erlo", 42};

b.insert(elem1.name, elem1);
b.insert(elem2.name, elem2);

b.erase(elem1.name);
EXPECT_EQ(b.size(), 1);
}

TEST(hashtable, EraseCorrectForEmptyHashTable) {
HashTable b;
b.erase("ame");
EXPECT_EQ(b.size(), 0);
}
