#include "s21_test.h"

namespace s21 {
TEST(QueueTest, Test1) {
  Queue<int> q;
  EXPECT_TRUE(q.empty());
  EXPECT_EQ(q.size(), 0u);
}

TEST(QueueTest, Test2) {
  Queue<int> q = {1, 2, 3};
  EXPECT_EQ(q.size(), 3u);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 3);
}

TEST(QueueTest, Test3) {
  Queue<std::string> q;
  q.push("first");
  q.push("second");
  EXPECT_EQ(q.front(), "first");
  EXPECT_EQ(q.back(), "second");
  EXPECT_EQ(q.size(), 2u);
}

TEST(QueueTest, Test4) {
  Queue<int> q = {10, 20, 30};
  q.pop();
  EXPECT_EQ(q.front(), 20);
  EXPECT_EQ(q.size(), 2u);
  q.pop();
  EXPECT_EQ(q.front(), 30);
  q.pop();
  EXPECT_TRUE(q.empty());
}

TEST(QueueTest, Test5) {
  Queue<int> q1 = {1, 2, 3};
  Queue<int> q2(q1);
  EXPECT_EQ(q1.size(), q2.size());
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 3);
}

TEST(QueueTest, Test6) {
  Queue<int> q1 = {4, 5, 6};
  Queue<int> q2(std::move(q1));
  EXPECT_EQ(q2.front(), 4);
  EXPECT_EQ(q2.size(), 3u);
  EXPECT_TRUE(q1.empty());
}

TEST(QueueTest, Test7) {
  Queue<int> q1 = {7, 8};
  Queue<int> q2;
  q2 = std::move(q1);
  EXPECT_EQ(q2.size(), 2u);
  EXPECT_EQ(q2.front(), 7);
  EXPECT_TRUE(q1.empty());
}

TEST(QueueTest, Test8) {
  Queue<int> q1 = {1, 2};
  Queue<int> q2 = {9};
  q1.swap(q2);
  EXPECT_EQ(q1.front(), 9);
  EXPECT_EQ(q1.size(), 1u);
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 2);
}

TEST(QueueTest, Test9) {
  Queue<char> q;
  EXPECT_TRUE(q.empty());
  q.push('a');
  EXPECT_FALSE(q.empty());
  q.pop();
  EXPECT_TRUE(q.empty());
}

TEST(QueueTest, Test10) {
  s21::Queue<int> queue;
  queue.insert_many_back(10);

  ASSERT_EQ(queue.size(), 1);
  EXPECT_EQ(queue.front(), 10);
  EXPECT_EQ(queue.back(), 10);
}

TEST(QueueTest, Test11) {
  s21::Queue<int> queue;
  queue.insert_many_back(1, 2, 3, 4);

  ASSERT_EQ(queue.size(), 4);
  EXPECT_EQ(queue.front(), 1);
  EXPECT_EQ(queue.back(), 4);

  queue.pop();
  EXPECT_EQ(queue.front(), 2);
  queue.pop();
  EXPECT_EQ(queue.front(), 3);
}

TEST(QueueTest, Test12) {
  s21::Queue<int> queue;
  queue.push(100);
  queue.insert_many_back(200, 300);

  ASSERT_EQ(queue.size(), 3);
  EXPECT_EQ(queue.front(), 100);
  EXPECT_EQ(queue.back(), 300);

  queue.pop();
  EXPECT_EQ(queue.front(), 200);
  queue.pop();
  EXPECT_EQ(queue.front(), 300);
}

TEST(QueueTest, Test13) {
  s21::Queue<std::string> queue;
  queue.insert_many_back("apple", "banana");

  ASSERT_EQ(queue.size(), 2);
  EXPECT_EQ(queue.front(), "apple");
  EXPECT_EQ(queue.back(), "banana");

  queue.pop();
  EXPECT_EQ(queue.front(), "banana");
}

}  // namespace s21