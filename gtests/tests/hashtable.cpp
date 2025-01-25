#include "gtest/gtest.h"
#include "HashTable.h"

// Unit tests for HashTable with TKey=int, TValue=string
TEST(HashTableIntStringTest, InsertAndSearch) {
    HashTable<int, string> table;

    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    // EXPECT_TRUE(table.exists(1));
    // EXPECT_TRUE(table.exists(2));
    // EXPECT_TRUE(table.exists(3));

    auto x =table.search(1);

    EXPECT_EQ(*table.search(1), string("one"));
    EXPECT_EQ(*table.search(2), string("two"));
    EXPECT_EQ(*table.search(3), string("three"));

    // Test for non-existent key
    EXPECT_FALSE(table.exists(4));
    EXPECT_EQ(table.search(4), nullptr);

    // Test for key replacement
    table.insert(1, "one_updated");
    EXPECT_EQ(*table.search(1), "one_updated");
}

// Unit tests for HashTable with TKey=int, TValue=int
TEST(HashTableIntIntTest, InsertAndSearch) {
    HashTable<int, int> table;

    table.insert(1, 10);
    table.insert(2, 20);
    table.insert(3, 30);

    EXPECT_TRUE(table.exists(1));
    EXPECT_TRUE(table.exists(2));
    EXPECT_TRUE(table.exists(3));

    EXPECT_EQ(*table.search(1), 10);
    EXPECT_EQ(*table.search(2), 20);
    EXPECT_EQ(*table.search(3), 30);

    // Test for non-existent key
    EXPECT_FALSE(table.exists(4));
    EXPECT_EQ(table.search(4), nullptr);

    // Test for key replacement
    table.insert(1, 11);
    EXPECT_EQ(*table.search(1), 11);
}

// Unit tests for HashTable with TKey=int, TValue=string
TEST(HashTableIntStringTest, Resize) {
    HashTable<int, string> table;

    // Insert elements until the load factor exceeds a threshold
    // (adjust the threshold and number of insertions based on your resize logic)
    for (int i = 0; i < 10; ++i) {
        table.insert(i, std::to_string(i));
    }

    // Verify that the load factor is within an acceptable range after resizing
    float loadFactor = table.loadFactor();
    EXPECT_LE(loadFactor, 0.75); // Example threshold, adjust as needed

    // Insert more elements to trigger another resize (if applicable)
    for (int i = 10; i < 20; ++i) {
        table.insert(i, std::to_string(i));
    }

    loadFactor = table.loadFactor();
    EXPECT_LE(loadFactor, 0.75); // Example threshold, adjust as needed
}

// Unit tests for HashTable with TKey=int, TValue=string
TEST(HashTableIntStringTest, ResizeAndKeepElements) {
    HashTable<int, string> table;

    const float MAX_FACTOR = 0.75f;

    const int p = 10 * MAX_FACTOR;

    for(int i=0; i < p; i++)
    {
        table.insert(i, std::to_string(i));
    }

    for(int i=0; i < p; i++)
    {
        EXPECT_EQ(table[i], std::to_string(i));
    }

    EXPECT_NEAR(table.loadFactor(), float(p) / 10, 0.1);

    for(int i=p; i < 10; i++)
    {
        table.insert(i, std::to_string(i));
    }


    EXPECT_NEAR(table.loadFactor(), 0.5, 0.1);
}