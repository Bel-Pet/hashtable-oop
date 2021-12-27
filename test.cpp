#include <gtest/gtest.h>
#include "hashtable.h"

TEST(hashtable, CorrectWorkResizeHashTable) {
    HashTable a;
    Value elements[10];
    elements[0].name = "vfgr";
    elements[0].age = 42;
    elements[1].name = "Eric";
    elements[1].age = 13;
    elements[2].name = "Erlo";
    elements[2].age = 42;
    elements[3].name = "Avgust";
    elements[3].age = 33;
    elements[4].name = "Jfwkesf";
    elements[4].age = 134;
    elements[5].name = "erte";
    elements[5].age = 13;
    elements[6].name = "jty";
    elements[6].age = 42;
    elements[7].name = "sdfs";
    elements[7].age = 33;
    elements[8].name = "vfg";
    elements[8].age = 134;
    elements[9].name = "erfge";
    elements[9].age = 13;

    a.insert("a", elements[0]);
    a.insert("b", elements[1]);
    a.insert("c", elements[2]);
    a.insert("d", elements[3]);
    a.insert("e", elements[4]);
    a.insert("f", elements[5]);
    a.insert("g", elements[6]);
    a.insert("h", elements[7]);
    a.insert("t", elements[8]);
    a.insert("y", elements[9]);

    EXPECT_TRUE(a.contains("a"));
    EXPECT_TRUE(a.contains("b"));
    EXPECT_TRUE(a.contains("c"));
    EXPECT_TRUE(a.contains("d"));
    EXPECT_TRUE(a.contains("e"));
    EXPECT_TRUE(a.contains("f"));
    EXPECT_TRUE(a.contains("g"));
    EXPECT_TRUE(a.contains("h"));
    EXPECT_TRUE(a.contains("t"));
    EXPECT_TRUE(a.contains("y"));
    EXPECT_EQ(a.size(), 10);
}

TEST(hashtable, CorrectWorkOperatorEqualsAndNotEquals) {
    HashTable a;
    Value elements[5];
    elements[0].name = "vfgr";
    elements[0].age = 42;
    elements[1].name = "Eric";
    elements[1].age = 13;
    elements[2].name = "Erlo";
    elements[2].age = 42;
    elements[3].name = "Avgust";
    elements[3].age = 33;
    elements[4].name = "Jfwkesf";
    elements[4].age = 134;

    a.insert("a", elements[0]);
    a.insert("b", elements[1]);
    a.insert("c", elements[2]);
    a.insert("d", elements[3]);

    HashTable b;
    b.insert("d", elements[3]);
    b.insert("c", elements[2]);
    b.insert("b", elements[1]);
    b.insert("a", elements[0]);

    bool result1 = a == b;
    bool result2 = a != b;

    EXPECT_TRUE(result1);
    EXPECT_TRUE(!result2);

    a.insert("e", elements[0]);
    b.insert("e", elements[1]);

    result1 = a == b;
    result2 = a != b;

    EXPECT_TRUE(!result1);
    EXPECT_TRUE(result2);

    a.erase("e");
    b.erase("e");
    result1 = a == b;
    result2 = a != b;

    EXPECT_TRUE(result1);
    EXPECT_TRUE(!result2);
}

TEST(hashtable, OperatorSquareBracketsWhenElementExisted) {
    HashTable a;
    Value element;
    element.name = "vfgr";
    element.age = 42;

    a.insert("a", element);

    Value result = a["a"];

    EXPECT_EQ(result.name, element.name);
    EXPECT_EQ(result.age, element.age);
    EXPECT_EQ(a.size(), 1);
}

TEST(hashtable, OperatorSquareBracketsWhenElementNotExisted) {
    HashTable a;
    Value elements[2];
    elements[0].name = "vfgr";
    elements[0].age = 42;
    elements[1].name = "Eric";
    elements[1].age = 13;

    a.insert("a", elements[0]);
    a.insert("b", elements[1]);

    Value result = a["d"];

    EXPECT_TRUE(result.name.empty());
    EXPECT_EQ(result.age, 0);
    EXPECT_EQ(a.size(), 3);
}

TEST(hashtable, CorrectWorkCopyConstructor) {
    HashTable a;
    Value elements[3];
    elements[0].name = "vfgr";
    elements[0].age = 42;
    elements[1].name = "Eric";
    elements[1].age = 13;
    elements[2].name = "Erlo";
    elements[2].age = 42;

    a.insert("a", elements[0]);
    a.insert("b", elements[1]);
    a.insert("c", elements[2]);


    HashTable b(a);

    EXPECT_EQ(b.size(), 3);
    EXPECT_TRUE(b.contains("a"));
    EXPECT_TRUE(b.contains("b"));
    EXPECT_TRUE(b.contains("c"));
}

TEST(hashtable, CorrectWorkOperatorAssignmentConstructor) {
    HashTable a;
    Value elements[5];
    elements[0].name = "vfgr";
    elements[0].age = 42;
    elements[1].name = "Eric";
    elements[1].age = 13;
    elements[2].name = "Erlo";
    elements[2].age = 42;
    elements[3].name = "Avgust";
    elements[3].age = 33;
    elements[4].name = "Jfwkesf";
    elements[4].age = 134;

    a.insert("a", elements[0]);
    a.insert("b", elements[1]);
    a.insert("c", elements[2]);

    HashTable b;

    b = a;

    EXPECT_EQ(b.size(), a.size());
    EXPECT_TRUE(b.contains("a"));
    EXPECT_TRUE(b.contains("b"));
    EXPECT_TRUE(b.contains("c"));
}

TEST(hashtable, CorrectContains) {
    HashTable a;
    Value elements[3];
    elements[0].name = "vfgr";
    elements[0].age = 42;
    elements[1].name = "Eric";
    elements[1].age = 13;
    elements[2].name = "Erlo";
    elements[2].age = 42;

    a.insert("a", elements[0]);
    a.insert("b", elements[1]);
    a.insert("c", elements[2]);

    EXPECT_TRUE(a.contains("a"));
    EXPECT_TRUE(a.contains("b"));
    EXPECT_TRUE(a.contains("c"));
}

TEST(hashtable, EmptyForEmptyHashTable) {
    HashTable a;
    EXPECT_TRUE(a.empty());
}

TEST(hashtable, EmptyForNotEmptyHashTable) {
    HashTable a;
    Value elements[3];
    elements[0].name = "vfgr";
    elements[0].age = 42;
    elements[1].name = "Eric";
    elements[1].age = 13;
    elements[2].name = "Erlo";
    elements[2].age = 42;

    a.insert("a", elements[0]);
    a.insert("b", elements[1]);
    a.insert("c", elements[2]);

    EXPECT_TRUE(!(a.empty()));
}

TEST(hashtable, SizeIsZeroForEmpty) {
    HashTable a;
    EXPECT_EQ(a.size(), 0);
}

TEST(hashtable, SizeIsNotEmpty) {
    HashTable a;
    Value elements[3];
    elements[0].name = "vfgr";
    elements[0].age = 42;
    elements[1].name = "Eric";
    elements[1].age = 13;
    elements[2].name = "Erlo";
    elements[2].age = 42;

    a.insert("a", elements[0]);
    a.insert("b", elements[1]);
    a.insert("c", elements[2]);

    EXPECT_EQ(a.size(), 3);
}

TEST(hashtable, SwapCorrect) {
    HashTable a;
    Value elements[3];
    elements[0].name = "vfgr";
    elements[0].age = 42;
    elements[1].name = "Eric";
    elements[1].age = 13;
    elements[2].name = "Erlo";
    elements[2].age = 42;

    a.insert("a", elements[0]);
    a.insert("b", elements[1]);
    a.insert("c", elements[2]);

    HashTable b;
    b.insert("a", elements[0]);
    b.insert("b", elements[1]);

    a.swap(b);

    EXPECT_EQ(a.size(), 2);
    EXPECT_EQ(b.size(), 3);
}

TEST(hashtable, ClearCorrectForNotEmptyHashTable) {
    HashTable a;
    Value elements[3];
    elements[0].name = "vfgr";
    elements[0].age = 42;
    elements[1].name = "Eric";
    elements[1].age = 13;
    elements[2].name = "Erlo";
    elements[2].age = 42;

    a.insert("a", elements[0]);
    a.insert("b", elements[1]);
    a.insert("c", elements[2]);

    a.clear();

    EXPECT_EQ(a.size(), 0);
}

TEST(hashtable, ClearCorrectForEmptyHashTable) {
    HashTable a;

    a.clear();

    EXPECT_EQ(a.size(), 0);
}

TEST(hashtable, EraseCorrectForNotEmptyHashTable) {
    HashTable a;
    Value elements[3];
    elements[0].name = "vfgr";
    elements[0].age = 42;
    elements[1].name = "Eric";
    elements[1].age = 13;
    elements[2].name = "Erlo";
    elements[2].age = 42;

    a.insert("a", elements[0]);
    a.insert("b", elements[1]);
    a.insert("c", elements[2]);
    a.erase("a");

    EXPECT_EQ(a.size(), 2);
}

TEST(hashtable, EraseCorrectForEmptyHashTable) {
    HashTable b;
    b.erase("ame");

    EXPECT_EQ(b.size(), 0);
}

TEST(hashtable, AtWhenElementExisted) {
    HashTable a;
    Value element;
    element.name = "vfgr";
    element.age = 42;

    a.insert("a", element);

    Value result = a.at("a");

    EXPECT_EQ(result.name, element.name);
    EXPECT_EQ(result.age, element.age);
}
