#include <gtest/gtest.h>

#include <initializer_list>
#include <stdexcept>
#include <string>
#include <utility>

#include "Vector.h"


// ============================================================
// Constructors
// ============================================================

TEST(VectorConstructorTest, SizeAndValue) {
    Vector<int> v(5, 42);

    EXPECT_EQ(v.size(), 5);
    EXPECT_EQ(v.capacity(), 5);

    for (std::size_t i = 0; i < v.size(); ++i) {
        EXPECT_EQ(v[i], 42);
    }
}

TEST(VectorConstructorTest, SizeOnly) {
    Vector<int> v(5);

    EXPECT_EQ(v.size(), 5);
    EXPECT_EQ(v.capacity(), 5);
}

TEST(VectorConstructorTest, InitializerList) {
    Vector<int> v{1, 2, 3, 4, 5};

    EXPECT_EQ(v.size(), 5);

    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
    EXPECT_EQ(v[3], 4);
    EXPECT_EQ(v[4], 5);
}

TEST(VectorConstructorTest, EmptyInitializerList) {
    Vector<int> v{};

    EXPECT_EQ(v.size(), 0);
    EXPECT_TRUE(v.empty());
}


// ============================================================
// Copy / Move
// ============================================================

TEST(VectorCopyTest, CopyConstructor) {
    Vector<int> original{1, 2, 3, 4};
    Vector<int> copy(original);

    EXPECT_EQ(copy.size(), original.size());

    for (std::size_t i = 0; i < original.size(); ++i) {
        EXPECT_EQ(copy[i], original[i]);
    }
}

TEST(VectorCopyTest, CopyIsIndependent) {
    Vector<int> original{1, 2, 3};
    Vector<int> copy(original);

    copy[0] = 100;

    EXPECT_EQ(original[0], 1);
    EXPECT_EQ(copy[0], 100);
}

TEST(VectorMoveTest, MoveConstructor) {
    Vector<int> original{1, 2, 3};
    Vector<int> moved(std::move(original));

    EXPECT_EQ(moved.size(), 3);
    EXPECT_EQ(moved[0], 1);
    EXPECT_EQ(moved[1], 2);
    EXPECT_EQ(moved[2], 3);
}

TEST(VectorAssignmentTest, CopyAssignment) {
    Vector<int> original{1, 2, 3};
    Vector<int> copy{10, 20};

    copy = original;

    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(copy[0], 1);
    EXPECT_EQ(copy[1], 2);
    EXPECT_EQ(copy[2], 3);
}

TEST(VectorAssignmentTest, MoveAssignment) {
    Vector<int> original{1, 2, 3};
    Vector<int> moved{10, 20};

    moved = std::move(original);

    EXPECT_EQ(moved.size(), 3);
    EXPECT_EQ(moved[0], 1);
    EXPECT_EQ(moved[1], 2);
    EXPECT_EQ(moved[2], 3);
}

TEST(VectorAssignmentTest, InitializerListAssignment) {
    Vector<int> v{1, 2, 3};

    v = {10, 20, 30, 40};

    EXPECT_EQ(v.size(), 4);
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);
    EXPECT_EQ(v[2], 30);
    EXPECT_EQ(v[3], 40);
}


// ============================================================
// Element access
// ============================================================

TEST(VectorAccessTest, SubscriptOperator) {
    Vector<int> v{10, 20, 30};

    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);
    EXPECT_EQ(v[2], 30);

    v[1] = 999;

    EXPECT_EQ(v[1], 999);
}

TEST(VectorAccessTest, ConstSubscriptOperator) {
    const Vector<int> v{10, 20, 30};

    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);
    EXPECT_EQ(v[2], 30);
}

TEST(VectorAccessTest, At) {
    Vector<int> v{10, 20, 30};

    EXPECT_EQ(v.at(0), 10);
    EXPECT_EQ(v.at(1), 20);
    EXPECT_EQ(v.at(2), 30);
}

TEST(VectorAccessTest, AtThrowsForOutOfBounds) {
    Vector<int> v{1, 2, 3};

    EXPECT_THROW(v.at(3), std::out_of_range);
    EXPECT_THROW(v.at(100), std::out_of_range);
}

TEST(VectorAccessTest, ConstAt) {
    const Vector<int> v{10, 20, 30};

    EXPECT_EQ(v.at(0), 10);
    EXPECT_EQ(v.at(2), 30);
}


// ============================================================
// push_back / pop_back
// ============================================================

TEST(VectorPushBackTest, PushBack) {
    Vector<int> v;

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);
    EXPECT_EQ(v[2], 30);
}

TEST(VectorPushBackTest, PushBackReallocates) {
    Vector<int> v;

    const auto old_capacity = v.capacity();

    v.push_back(1);

    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v[0], 1);

    EXPECT_GE(v.capacity(), old_capacity);
}

TEST(VectorPushBackTest, ManyElements) {
    Vector<int> v;

    for (int i = 0; i < 1000; ++i) {
        v.push_back(i);
    }

    EXPECT_EQ(v.size(), 1000);

    for (int i = 0; i < 1000; ++i) {
        EXPECT_EQ(v[i], i);
    }
}

TEST(VectorPopBackTest, PopBack) {
    Vector<int> v{1, 2, 3};

    v.pop_back();

    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v.back(), 2);

    v.pop_back();

    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v.back(), 1);

    v.pop_back();

    EXPECT_EQ(v.size(), 0);
    EXPECT_TRUE(v.empty());
}


// ============================================================
// emplace_back
// ============================================================

TEST(VectorEmplaceBackTest, EmplaceBack) {
    Vector<std::string> v;

    std::string value = "hello";

    v.emplace_back(std::move(value));

    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v[0], "hello");
}


// ============================================================
// front / back
// ============================================================

TEST(VectorFrontBackTest, Front) {
    Vector<int> v{10, 20, 30};

    EXPECT_EQ(v.front(), 10);

    v.front() = 100;

    EXPECT_EQ(v[0], 100);
}

TEST(VectorFrontBackTest, ConstFront) {
    const Vector<int> v{10, 20, 30};

    EXPECT_EQ(v.front(), 10);
}

TEST(VectorFrontBackTest, Back) {
    Vector<int> v{10, 20, 30};

    EXPECT_EQ(v.back(), 30);

    v.back() = 100;

    EXPECT_EQ(v[2], 100);
}

TEST(VectorFrontBackTest, ConstBack) {
    const Vector<int> v{10, 20, 30};

    EXPECT_EQ(v.back(), 30);
}


// ============================================================
// data
// ============================================================

TEST(VectorDataTest, DataPointsToFirstElement) {
    Vector<int> v{10, 20, 30};

    int* data = v.data();

    ASSERT_NE(data, nullptr);

    EXPECT_EQ(data[0], 10);
    EXPECT_EQ(data[1], 20);
    EXPECT_EQ(data[2], 30);
}

TEST(VectorDataTest, DataCanModifyElements) {
    Vector<int> v{1, 2, 3};

    v.data()[1] = 100;

    EXPECT_EQ(v[1], 100);
}

TEST(VectorDataTest, ConstData) {
    const Vector<int> v{1, 2, 3};

    const int* data = v.data();

    EXPECT_EQ(data[0], 1);
    EXPECT_EQ(data[1], 2);
    EXPECT_EQ(data[2], 3);
}


// ============================================================
// empty / size / capacity
// ============================================================

TEST(VectorStateTest, EmptyInitially) {
    Vector<int> v;

    EXPECT_TRUE(v.empty());
    EXPECT_EQ(v.size(), 0);
}

TEST(VectorStateTest, NotEmptyAfterPushBack) {
    Vector<int> v;

    v.push_back(42);

    EXPECT_FALSE(v.empty());
    EXPECT_EQ(v.size(), 1);
}

TEST(VectorStateTest, CapacityIsAtLeastSize) {
    Vector<int> v;

    for (int i = 0; i < 100; ++i) {
        v.push_back(i);

        EXPECT_GE(v.capacity(), v.size());
    }
}


// ============================================================
// reserve
// ============================================================

TEST(VectorReserveTest, ReserveIncreasesCapacity) {
    Vector<int> v;

    v.reserve(100);

    EXPECT_GE(v.capacity(), 100);
    EXPECT_EQ(v.size(), 0);
}

TEST(VectorReserveTest, ReserveDoesNotChangeSize) {
    Vector<int> v{1, 2, 3};

    v.reserve(100);

    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
}

TEST(VectorReserveTest, ReservePreservesElements) {
    Vector<int> v{1, 2, 3, 4, 5};

    v.reserve(100);

    EXPECT_EQ(v.size(), 5);

    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(v[i], i + 1);
    }
}


// ============================================================
// resize
// ============================================================

TEST(VectorResizeTest, ResizeLarger) {
    Vector<int> v{1, 2, 3};

    v.resize(5);

    EXPECT_EQ(v.size(), 5);

    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
}

TEST(VectorResizeTest, ResizeSmaller) {
    Vector<int> v{1, 2, 3, 4, 5};

    v.resize(2);

    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
}

TEST(VectorResizeTest, ResizeToZero) {
    Vector<int> v{1, 2, 3};

    v.resize(0);

    EXPECT_EQ(v.size(), 0);
    EXPECT_TRUE(v.empty());
}


// ============================================================
// Iterators
// ============================================================

TEST(VectorIteratorTest, BeginEnd) {
    Vector<int> v{1, 2, 3};

    auto it = v.begin();
    auto end = v.end();

    EXPECT_EQ(*it, 1);

    ++it;
    EXPECT_EQ(*it, 2);

    ++it;
    EXPECT_EQ(*it, 3);

    ++it;

    EXPECT_EQ(it, end);
}

TEST(VectorIteratorTest, PrefixIncrement) {
    Vector<int> v{1, 2, 3};

    auto it = v.begin();

    EXPECT_EQ(*++it, 2);
    EXPECT_EQ(*++it, 3);
}

TEST(VectorIteratorTest, PostfixIncrement) {
    Vector<int> v{1, 2, 3};

    auto it = v.begin();

    auto old = it++;

    EXPECT_EQ(*old, 1);
    EXPECT_EQ(*it, 2);
}

TEST(VectorIteratorTest, PrefixDecrement) {
    Vector<int> v{1, 2, 3};

    auto it = v.end();

    --it;

    EXPECT_EQ(*it, 3);

    --it;

    EXPECT_EQ(*it, 2);
}

TEST(VectorIteratorTest, PostfixDecrement) {
    Vector<int> v{1, 2, 3};

    auto it = v.end();

    auto old = it--;

    EXPECT_EQ(old, v.end());
    EXPECT_EQ(*it, 3);
}

TEST(VectorIteratorTest, IteratorAddition) {
    Vector<int> v{10, 20, 30, 40};

    auto it = v.begin();

    EXPECT_EQ(*(it + 0), 10);
    EXPECT_EQ(*(it + 1), 20);
    EXPECT_EQ(*(it + 2), 30);
    EXPECT_EQ(*(it + 3), 40);
}

TEST(VectorIteratorTest, IteratorSubtraction) {
    Vector<int> v{10, 20, 30, 40};

    auto it = v.end();

    EXPECT_EQ(*(it - 1), 40);
    EXPECT_EQ(*(it - 2), 30);
    EXPECT_EQ(*(it - 3), 20);
}

TEST(VectorIteratorTest, RangeBasedFor) {
    Vector<int> v{1, 2, 3, 4, 5};

    int expected = 1;

    for (int x : v) {
        EXPECT_EQ(x, expected);
        ++expected;
    }

    EXPECT_EQ(expected, 6);
}


// ============================================================
// Different types
// ============================================================

TEST(VectorTypeTest, WorksWithString) {
    Vector<std::string> v{
        "hello",
        "world",
        "vector"
    };

    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0], "hello");
    EXPECT_EQ(v[1], "world");
    EXPECT_EQ(v[2], "vector");
}

TEST(VectorTypeTest, WorksWithDouble) {
    Vector<double> v{
        1.5,
        2.5,
        3.5
    };

    EXPECT_DOUBLE_EQ(v[0], 1.5);
    EXPECT_DOUBLE_EQ(v[1], 2.5);
    EXPECT_DOUBLE_EQ(v[2], 3.5);
}

