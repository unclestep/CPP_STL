#include "s21_test.h"

namespace s21{
    TEST(QueueTest, DefaultConstructor) {
        Queue<int> q;
        EXPECT_TRUE(q.empty());
        EXPECT_EQ(q.size(), 0u);
    }

    TEST(QueueTest, InitializerListConstructor) {
        Queue<int> q = {1, 2, 3};
        EXPECT_EQ(q.size(), 3u);
        EXPECT_EQ(q.front(), 1);
        EXPECT_EQ(q.back(), 3);
    }

    TEST(QueueTest, PushBackAndFront) {
        Queue<std::string> q;
        q.push("first");
        q.push("second");
        EXPECT_EQ(q.front(), "first");
        EXPECT_EQ(q.back(), "second");
        EXPECT_EQ(q.size(), 2u);
    }

    TEST(QueueTest, Pop) {
        Queue<int> q = {10, 20, 30};
        q.pop();
        EXPECT_EQ(q.front(), 20);
        EXPECT_EQ(q.size(), 2u);
        q.pop();
        EXPECT_EQ(q.front(), 30);
        q.pop();
        EXPECT_TRUE(q.empty());
    }

    TEST(QueueTest, CopyConstructor) {
        Queue<int> q1 = {1, 2, 3};
        Queue<int> q2(q1);
        EXPECT_EQ(q1.size(), q2.size());
        EXPECT_EQ(q2.front(), 1);
        EXPECT_EQ(q2.back(), 3);
    }

    TEST(QueueTest, MoveConstructor) {
        Queue<int> q1 = {4, 5, 6};
        Queue<int> q2(std::move(q1));
        EXPECT_EQ(q2.front(), 4);
        EXPECT_EQ(q2.size(), 3u);
        EXPECT_TRUE(q1.empty());
    }

    TEST(QueueTest, MoveAssignmentOperator) {
        Queue<int> q1 = {7, 8};
        Queue<int> q2;
        q2 = std::move(q1);
        EXPECT_EQ(q2.size(), 2u);
        EXPECT_EQ(q2.front(), 7);
        EXPECT_TRUE(q1.empty());
    }

    TEST(QueueTest, Swap) {
        Queue<int> q1 = {1, 2};
        Queue<int> q2 = {9};
        q1.swap(q2);
        EXPECT_EQ(q1.front(), 9);
        EXPECT_EQ(q1.size(), 1u);
        EXPECT_EQ(q2.front(), 1);
        EXPECT_EQ(q2.back(), 2);
    }

    TEST(QueueTest, EmptyTrueFalse) {
        Queue<char> q;
        EXPECT_TRUE(q.empty());
        q.push('a');
        EXPECT_FALSE(q.empty());
        q.pop();
        EXPECT_TRUE(q.empty());
    }
}