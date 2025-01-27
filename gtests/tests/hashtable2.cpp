#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "HashTable.h"  // Replace with the actual header file

// Fixture for the HashTable class template
template <typename TKey, typename TValue>
class HashTableTest : public ::testing::Test {
protected:
    void SetUp() override {
        table = std::unique_ptr<HashTable<TKey, TValue>>(new HashTable<TKey, TValue>());
    }

    std::unique_ptr<HashTable<TKey, TValue>> table;
};

// Typedefs for specific test types
using IntStringHashTableTest = HashTableTest<int, std::string>;
using IntIntHashTableTest = HashTableTest<int, int>;

// Test cases for int, std::string specialization
TEST_F(IntStringHashTableTest, InsertAndResize) {
    const int initialSize = 10;
    const float maxLoadFactor = 0.75f; // Assumed max load factor

    // Insert enough elements to trigger a resize
    for (int i = 0; i < initialSize; ++i) {
        table->insert(i, "value" + std::to_string(i));
    }

    // Verify load factor before resizing
    float loadFactorBefore = table->loadFactor();
    ASSERT_NEAR(loadFactorBefore, static_cast<float>(initialSize) / initialSize, 0.01);

    // Insert one more element to trigger resize
    table->insert(initialSize, "trigger_resize");

    // Verify load factor after resizing
    float loadFactorAfter = table->loadFactor();
    ASSERT_LT(loadFactorAfter, maxLoadFactor);

    // Verify all original elements are still present
    for (int i = 0; i < initialSize; ++i) {
        auto value = table->search(i);
        ASSERT_NE(value, nullptr);
        ASSERT_EQ(*value, "value" + std::to_string(i));
    }

    // Verify the newly added element is present
    auto newValue = table->search(initialSize);
    ASSERT_NE(newValue, nullptr);
    ASSERT_EQ(*newValue, "trigger_resize");
}

// Test cases for int, int specialization
TEST_F(IntIntHashTableTest, InsertAndResize) {
    const int initialSize = 10;
    const float maxLoadFactor = 0.75f; // Assumed max load factor

    // Insert enough elements to trigger a resize
    for (int i = 0; i < initialSize; ++i) {
        table->insert(i, i * 10);
    }

    // Verify load factor before resizing
    float loadFactorBefore = table->loadFactor();
    ASSERT_NEAR(loadFactorBefore, static_cast<float>(initialSize) / initialSize, 0.01);

    // Insert one more element to trigger resize
    table->insert(initialSize, 999);

    // Verify load factor after resizing
    float loadFactorAfter = table->loadFactor();
    ASSERT_LT(loadFactorAfter, maxLoadFactor);

    // Verify all original elements are still present
    for (int i = 0; i < initialSize; ++i) {
        auto value = table->search(i);
        ASSERT_NE(value, nullptr);
        ASSERT_EQ(*value, i * 10);
    }

    // Verify the newly added element is present
    auto newValue = table->search(initialSize);
    ASSERT_NE(newValue, nullptr);
    ASSERT_EQ(*newValue, 999);
}
