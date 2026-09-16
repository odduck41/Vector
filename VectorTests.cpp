
#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "Vector.h"

// ============================================================
// Empty vector
// ============================================================

TEST(VectorEdgeTest, DefaultConstructedVector) {
    Vector<int> v;

    EXPECT_EQ(v.size(), 0);
    EXPECT_TRUE(v.empty());
    EXPECT_EQ(v.capacity(), 1);
}

TEST(VectorEdgeTest, EmptyInitializerList) {
    Vector<int> v{};

    EXPECT_EQ(v.size(), 0);
    EXPECT_TRUE(v.empty());
}

TEST(VectorEdgeTest, EmptyVectorCanBeFilledAfterConstruction) {
    Vector<int> v;

    v.push_back(10);
    v.push_back(20);

    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);
}

// ============================================================
// push_back / reallocation
// ============================================================

TEST(VectorPushBackTest, ElementsSurviveRepeatedReallocation) {
    Vector<int> v;

    for (int i = 0; i < 10000; ++i) {
        v.push_back(i);
    }

    ASSERT_EQ(v.size(), 10000);

    for (int i = 0; i < 10000; ++i) {
        EXPECT_EQ(v[i], i);
    }
}

TEST(VectorPushBackTest, CapacityNeverBelowSize) {
    Vector<int> v;

    for (int i = 0; i < 1000; ++i) {
        v.push_back(i);

        EXPECT_GE(v.capacity(), v.size());
    }
}

TEST(VectorPushBackTest, PushBackAfterResizeToZero) {
    Vector<int> v{1, 2, 3};

    v.resize(0);

    ASSERT_TRUE(v.empty());

    v.push_back(42);

    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v[0], 42);
}

TEST(VectorPushBackTest, PushBackAfterReserve) {
    Vector<int> v;

    v.reserve(100);

    const auto capacity = v.capacity();

    for (int i = 0; i < 99; ++i) {
        v.push_back(i);
    }

    EXPECT_EQ(v.capacity(), capacity);
    EXPECT_EQ(v.size(), 99);

    for (int i = 0; i < 99; ++i) {
        EXPECT_EQ(v[i], i);
    }
}

// ============================================================
// pop_back
// ============================================================

TEST(VectorPopBackTest, PopBackPreservesRemainingElements) {
    Vector<int> v{1, 2, 3, 4, 5};

    v.pop_back();

    ASSERT_EQ(v.size(), 4);

    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
    EXPECT_EQ(v[3], 4);
}

TEST(VectorPopBackTest, PushAfterPop) {
    Vector<int> v{1, 2, 3};

    v.pop_back();
    v.push_back(42);

    ASSERT_EQ(v.size(), 3);

    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 42);
}

TEST(VectorPopBackTest, CapacityDoesNotDecrease) {
    Vector<int> v{1, 2, 3, 4, 5};

    const auto capacity = v.capacity();

    v.pop_back();
    v.pop_back();
    v.pop_back();

    EXPECT_EQ(v.capacity(), capacity);
}

// ============================================================
// resize
// ============================================================

TEST(VectorResizeTest, ResizeLargerPreservesExistingElements) {
    Vector<int> v{10, 20, 30};

    v.resize(100);

    ASSERT_EQ(v.size(), 100);

    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);
    EXPECT_EQ(v[2], 30);
}

TEST(VectorResizeTest, ResizeLargerThenPushBack) {
    Vector<int> v{1, 2};

    v.resize(10);
    v.push_back(42);

    EXPECT_EQ(v.size(), 11);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[10], 42);
}

TEST(VectorResizeTest, ResizeSmallerThenGrowAgain) {
    Vector<int> v{1, 2, 3, 4, 5};

    v.resize(2);
    v.resize(5);

    EXPECT_EQ(v.size(), 5);

    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
}

TEST(VectorResizeTest, ResizeToSameSize) {
    Vector<int> v{1, 2, 3};

    const auto capacity = v.capacity();

    v.resize(3);

    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v.capacity(), capacity);

    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
}

TEST(VectorResizeTest, ResizeZeroThenGrow) {
    Vector<int> v{1, 2, 3};

    v.resize(0);
    v.resize(5);

    EXPECT_EQ(v.size(), 5);

    v[0] = 100;
    v[4] = 500;

    EXPECT_EQ(v[0], 100);
    EXPECT_EQ(v[4], 500);
}

// ============================================================
// reserve
// ============================================================

TEST(VectorReserveTest, ReserveSmallerThanCapacityDoesNothing) {
    Vector<int> v{1, 2, 3, 4};

    const auto capacity = v.capacity();

    v.reserve(1);

    EXPECT_EQ(v.capacity(), capacity);
    EXPECT_EQ(v.size(), 4);
}

TEST(VectorReserveTest, ReserveExactlyCurrentCapacityDoesNothing) {
    Vector<int> v{1, 2, 3};

    const auto capacity = v.capacity();

    v.reserve(capacity);

    EXPECT_EQ(v.capacity(), capacity);
    EXPECT_EQ(v.size(), 3);
}

TEST(VectorReserveTest, MultipleReserveCallsPreserveElements) {
    Vector<int> v{1, 2, 3};

    v.reserve(10);
    v.reserve(100);
    v.reserve(1000);

    EXPECT_EQ(v.size(), 3);

    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
}

// ============================================================
// Copy semantics
// ============================================================

TEST(VectorCopyTest, CopyAssignmentIsIndependent) {
    Vector<int> a{1, 2, 3};
    Vector<int> b{10, 20, 30};

    b = a;

    b[0] = 100;

    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(b[0], 100);
}

TEST(VectorCopyTest, SelfAssignment) {
    Vector<int> v{1, 2, 3};

    v = v;

    ASSERT_EQ(v.size(), 3);

    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
}

TEST(VectorCopyTest, CopyEmptyVector) {
    Vector<int> a;

    Vector<int> b(a);

    EXPECT_EQ(b.size(), 0);
    EXPECT_TRUE(b.empty());
}

TEST(VectorCopyTest, AssignEmptyVector) {
    Vector<int> a{1, 2, 3};
    Vector<int> b;

    a = b;

    EXPECT_EQ(a.size(), 0);
    EXPECT_TRUE(a.empty());
}

// ============================================================
// Move semantics
// ============================================================

TEST(VectorMoveTest, MoveAssignmentTransfersElements) {
    Vector<int> source{1, 2, 3, 4};

    Vector<int> destination{10, 20};

    destination = std::move(source);

    ASSERT_EQ(destination.size(), 4);

    EXPECT_EQ(destination[0], 1);
    EXPECT_EQ(destination[1], 2);
    EXPECT_EQ(destination[2], 3);
    EXPECT_EQ(destination[3], 4);
}

TEST(VectorMoveTest, MoveConstructorTransfersElements) {
    Vector<std::string> source{
        "one",
        "two",
        "three"
    };

    Vector<std::string> destination(std::move(source));

    ASSERT_EQ(destination.size(), 3);

    EXPECT_EQ(destination[0], "one");
    EXPECT_EQ(destination[1], "two");
    EXPECT_EQ(destination[2], "three");
}

// ============================================================
// Initializer list
// ============================================================

TEST(VectorInitializerListTest, AssignmentShrinksVector) {
    Vector<int> v{1, 2, 3, 4, 5};

    v = {10, 20};

    ASSERT_EQ(v.size(), 2);

    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);
}

TEST(VectorInitializerListTest, AssignmentToEmptyList) {
    Vector<int> v{1, 2, 3};

    v = {};

    EXPECT_EQ(v.size(), 0);
    EXPECT_TRUE(v.empty());
}

// ============================================================
// Element access
// ============================================================

TEST(VectorAccessTest, AtAllowsLastElement) {
    Vector<int> v{10, 20, 30};

    EXPECT_EQ(v.at(2), 30);
}

TEST(VectorAccessTest, AtRejectsSize) {
    Vector<int> v{10, 20, 30};

    EXPECT_THROW(v.at(v.size()), std::out_of_range);
}

TEST(VectorAccessTest, AtRejectsHugeIndex) {
    Vector<int> v{1, 2, 3};

    EXPECT_THROW(v.at(1000000), std::out_of_range);
}

TEST(VectorAccessTest, SubscriptReturnsReference) {
    Vector<int> v{1, 2, 3};

    int& ref = v[1];

    ref = 999;

    EXPECT_EQ(v[1], 999);
}

// ============================================================
// front / back
// ============================================================

TEST(VectorFrontBackTest, FrontAndBackReferToSameVector) {
    Vector<int> v{1, 2, 3};

    v.front() = 100;
    v.back() = 300;

    EXPECT_EQ(v[0], 100);
    EXPECT_EQ(v[2], 300);
}

TEST(VectorFrontBackTest, FrontAndBackRemainValidAfterResize) {
    Vector<int> v{1, 2, 3, 4};

    v.resize(2);

    EXPECT_EQ(v.front(), 1);
    EXPECT_EQ(v.back(), 2);
}

// ============================================================
// data
// ============================================================

TEST(VectorDataTest, DataMatchesSubscript) {
    Vector<int> v{10, 20, 30, 40};

    int* ptr = v.data();

    for (std::size_t i = 0; i < v.size(); ++i) {
        EXPECT_EQ(ptr[i], v[i]);
    }
}

TEST(VectorDataTest, DataCanBeUsedForMutation) {
    Vector<int> v{1, 2, 3};

    int* ptr = v.data();

    ptr[0] = 100;
    ptr[1] = 200;
    ptr[2] = 300;

    EXPECT_EQ(v[0], 100);
    EXPECT_EQ(v[1], 200);
    EXPECT_EQ(v[2], 300);
}

// ============================================================
// Iterator invariants
// ============================================================

TEST(VectorIteratorTest, EmptyVectorBeginEqualsEnd) {
    Vector<int> v;

    EXPECT_EQ(v.begin(), v.end());
}

TEST(VectorIteratorTest, IteratorWalksExactlySizeElements) {
    Vector<int> v{10, 20, 30, 40, 50};

    std::size_t count = 0;

    for (auto it = v.begin(); it != v.end(); ++it) {
        ++count;
    }

    EXPECT_EQ(count, v.size());
}

TEST(VectorIteratorTest, IteratorCanModifyElements) {
    Vector<int> v{1, 2, 3};

    for (auto it = v.begin(); it != v.end(); ++it) {
        *it *= 10;
    }

    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);
    EXPECT_EQ(v[2], 30);
}

TEST(VectorIteratorTest, AdditionAndSubtractionAreConsistent) {
    Vector<int> v{10, 20, 30, 40, 50};

    auto begin = v.begin();
    auto end = v.end();

    EXPECT_EQ(begin + 5, end);
    EXPECT_EQ(end - 5, begin);

    EXPECT_EQ(*(begin + 2), 30);
    EXPECT_EQ(*(end - 2), 40);
}

TEST(VectorIteratorTest, PrefixAndPostfixIncrementHaveCorrectSemantics) {
    Vector<int> v{10, 20, 30};

    auto it = v.begin();

    auto old = it++;

    EXPECT_EQ(*old, 10);
    EXPECT_EQ(*it, 20);

    auto& result = ++it;

    EXPECT_EQ(&result, &it);
    EXPECT_EQ(*it, 30);
}

TEST(VectorIteratorTest, PrefixAndPostfixDecrementHaveCorrectSemantics) {
    Vector<int> v{10, 20, 30};

    auto it = v.end();

    auto old = it--;

    EXPECT_EQ(old, v.end());
    EXPECT_EQ(*it, 30);

    auto& result = --it;

    EXPECT_EQ(&result, &it);
    EXPECT_EQ(*it, 20);
}

// ============================================================
// Iterator mutation + vector state
// ============================================================

TEST(VectorIteratorTest, RangeForCanModifyElements) {
    Vector<int> v{1, 2, 3, 4};

    for (auto& x : v) {
        x *= 2;
    }

    EXPECT_EQ(v[0], 2);
    EXPECT_EQ(v[1], 4);
    EXPECT_EQ(v[2], 6);
    EXPECT_EQ(v[3], 8);
}

// ============================================================
// Different element types
// ============================================================

TEST(VectorTypeTest, StringPushBack) {
    Vector<std::string> v;

    v.push_back("hello");
    v.push_back("world");

    ASSERT_EQ(v.size(), 2);

    EXPECT_EQ(v[0], "hello");
    EXPECT_EQ(v[1], "world");
}

TEST(VectorTypeTest, StringResize) {
    Vector<std::string> v{"a", "b"};

    v.resize(10);

    ASSERT_EQ(v.size(), 10);

    EXPECT_EQ(v[0], "a");
    EXPECT_EQ(v[1], "b");
}

TEST(VectorTypeTest, DoubleValues) {
    Vector<double> v;

    v.push_back(0.1);
    v.push_back(1.5);
    v.push_back(-3.75);

    EXPECT_DOUBLE_EQ(v[0], 0.1);
    EXPECT_DOUBLE_EQ(v[1], 1.5);
    EXPECT_DOUBLE_EQ(v[2], -3.75);
}

// ============================================================
// Stateful / mixed-operation tests
// ============================================================

TEST(VectorStateTest, MixedOperationsPreserveLogicalSequence) {
    Vector<int> v;

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    v.pop_back();

    v.push_back(4);

    v.reserve(100);

    v.resize(5);

    v[3] = 40;
    v[4] = 50;

    v.resize(4);

    ASSERT_EQ(v.size(), 4);

    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 4);
    EXPECT_EQ(v[3], 40);
}

TEST(VectorStateTest, RepeatedGrowShrinkCycle) {
    Vector<int> v;

    for (int cycle = 0; cycle < 100; ++cycle) {
        for (int i = 0; i < 100; ++i) {
            v.push_back(i);
        }

        ASSERT_EQ(v.size(), 100);

        for (int i = 0; i < 100; ++i) {
            EXPECT_EQ(v[i], i);
        }

        v.resize(0);

        EXPECT_TRUE(v.empty());
    }
}

