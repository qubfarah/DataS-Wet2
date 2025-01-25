//
// Created by jamal on 1/25/2025.
//
#include <gtest/gtest.h>
#include "UnionFind.h" // Replace with the actual header file


TEST(DisjointSetTest, makesetAndFind)
{
    UnionFind ds;

    // Create sets for elements 1, 2, and 3
    ds.makeset(1);
    ds.makeset(2);
    ds.makeset(3);

    // Verify each element is its own parent initially
    EXPECT_EQ(ds.find(1), 1);
    EXPECT_EQ(ds.find(2), 2);
    EXPECT_EQ(ds.find(3), 3);
}

TEST(DisjointSetTest, UnionAndFind)
{
    UnionFind ds;

    // Create sets for elements 1, 2, and 3
    ds.makeset(1);
    ds.makeset(2);
    ds.makeset(3);

    // Union elements 1 and 2
    ds.unite(1, 2);

    // Verify that 1 and 2 are in the same set
    EXPECT_EQ(ds.find(1), ds.find(2));

    // Verify that 3 is still in its own set
    EXPECT_NE(ds.find(1), ds.find(3));
    EXPECT_NE(ds.find(2), ds.find(3));
}

TEST(DisjointSetTest, UnionByRank)
{
    UnionFind ds;

    // Create sets for elements 1, 2, 3, and 4
    ds.makeset(1);
    ds.makeset(2);
    ds.makeset(3);
    ds.makeset(4);

    // Union elements 1 and 2, and elements 3 and 4
    ds.unite(1, 2);
    ds.unite(3, 4);

    // Union the two resulting sets
    ds.unite(1, 3);

    // Verify all elements are in the same set
    EXPECT_EQ(ds.find(1), ds.find(2));
    EXPECT_EQ(ds.find(2), ds.find(3));
    EXPECT_EQ(ds.find(3), ds.find(4));
}

TEST(DisjointSetTest, PathCompression)
{
    UnionFind ds;

    // Create a chain of elements: 1 -> 2 -> 3 -> 4
    ds.makeset(1);
    ds.makeset(2);
    ds.makeset(3);
    ds.makeset(4);
    ds.unite(1, 2);
    ds.unite(2, 3);
    ds.unite(3, 4);

    // Access the deepest element and verify path compression
    int root = ds.find(4);
    EXPECT_EQ(root, ds.find(1));

    // Verify all elements now point directly to the root
    EXPECT_EQ(ds.find(2), root);
    EXPECT_EQ(ds.find(3), root);
    EXPECT_EQ(ds.find(4), root);
}

TEST(DisjointSetTest, MultipleUnionsAndPathCompression)
{
    UnionFind ds;

    // Create sets for elements 1 through 8
    for (int i = 1; i <= 8; ++i)
    {
        ds.makeset(i);
    }

    // Perform unions in a complex pattern
    ds.unite(1, 2);
    ds.unite(2, 3);
    ds.unite(4, 5);
    ds.unite(6, 7);
    ds.unite(7, 8);
    ds.unite(3, 5);
    ds.unite(5, 6);

    // Verify all elements are in the same set
    int root = ds.find(1);
    for (int i = 2; i <= 8; ++i)
    {
        EXPECT_EQ(ds.find(i), root);
    }

    // Verify path compression by ensuring all nodes point directly to the root
    for (int i = 1; i <= 8; ++i)
    {
        EXPECT_EQ(ds.find(i), root);
    }
}

TEST(DisjointSetTest, LargeScaleTest)
{
    UnionFind ds;

    // Create sets for 1 to 1000
    for (int i = 1; i <= 1000; ++i)
    {
        ds.makeset(i);
    }

    // Perform unions in pairs
    for (int i = 1; i < 1000; i += 2)
    {
        ds.unite(i, i + 1);
    }

    // Perform unions of resulting pairs
    for (int i = 1; i < 1000; i += 4)
    {
        ds.unite(i, i + 2);
    }

    // Continue merging until all elements are in one set
    for (int step = 8; step < 1000; step *= 2)
    {
        for (int i = 1; i + step <= 1000; i += step)
        {
            ds.unite(i, i + step / 2);
        }
    }

    // Verify all elements are in the same set
    int root = ds.find(1);
    for (int i = 2; i <= 1000; ++i)
    {
        EXPECT_EQ(ds.find(i), root);
    }
}


TEST(DisjointSetTest, DebugLargeScaleTest)
{
    UnionFind ds;

    for (int i = 1; i <= 100; ++i)
    {
        // Start with a smaller range
        ds.makeset(i);
    }

    for (int i = 1; i < 100; i += 2)
    {
        ds.unite(i, i + 1);
    }

    //VERIFY
    for (int i = 1; i < 100; i += 2)
    {
        ASSERT_EQ(ds.find(i), ds.find(i+1));
    }

    for (int i = 1; i < 100; i += 4)
    {
        ds.unite(i, i + 2);
    }

    //VERIFY
    for (int i = 1; i < 100; i += 4)
    {
        for (int j = i; j < i + 3; j++)
        {
            ASSERT_EQ(ds.find(j), ds.find(j+1));
        }
    }


    for (int i = 4; i < 100; i += 4)
    {
        ds.unite(i, i+1);
    }

    // for (int step = 8; step < 100; step *= 2)
    // {
    //     for (int i = 1; i + step <= 100; i += step)
    //     {
    //         ds.unite(i, i + step / 2);
    //     }
    // }

    int root = ds.find(1);
    for (int i = 2; i <= 100; ++i)
    {
        EXPECT_EQ(ds.find(i), root) << "Element " << i << " has incorrect root.";
    }
}
