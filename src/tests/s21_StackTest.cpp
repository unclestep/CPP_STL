//
// Created by rasko on 06.04.2025.
//
#include "s21_test.h"

namespace s21 {
TEST(StackTests, Test1) { Stack<int> s1; }
TEST(StackTests, Test2) {
  Stack<int> s1{1, 2, 3, 4, 5};

  EXPECT_EQ(s1.top(), 5);
}
TEST(StackTests, Test3) {
  Stack<int> s1;

  EXPECT_EQ(s1.empty(), true);
}
TEST(StackTests, Test4) {
  Stack<int> s1{1};

  EXPECT_EQ(s1.empty(), false);
}
TEST(StackTests, Test5) {
  Stack<int> s1{1, 2, 3, 4, 5, 6};
  EXPECT_EQ(s1.size(), 6);
}
TEST(StackTests, Test6) {
  Stack<int> s1{1, 2, 3, 4, 5, 6};
  EXPECT_EQ(s1.size(), 6);
}
TEST(StackTests, Test7) {
  Stack<int> s1{1, 2, 3, 4, 5, 6};
  s1.push(7);
  EXPECT_EQ(s1.top(), 7);
}
TEST(StackTests, Test8) {
  Stack<int> s1{1, 2, 3, 4, 5, 6};
  s1.pop();
  EXPECT_EQ(s1.top(), 5);
}
TEST(StackTests, Test9) {
  Stack<int> s1{1, 2, 3, 4, 5, 6};
  Stack<int> s2{11, 12, 13};
  s1.swap(s2);
  EXPECT_EQ(s1.top(), 13);
  EXPECT_EQ(s2.top(), 6);
}
TEST(StackTests, Test10) {
  Stack<int> s1{1, 2, 3, 4, 5, 6};
  Stack<int> s2 = s1;
  EXPECT_EQ(s1.top(), 6);
  EXPECT_EQ(s2.top(), 6);
}
TEST(StackTests, Test11) {
  Stack<int> s1{1, 2, 3, 4, 5, 6};
  Stack<int> s2(s1);

  EXPECT_EQ(s1.top(), s2.top());
}
TEST(StackTests, Test12) {
  Stack<int> s1{1, 2, 3, 4, 5, 6};
  Stack<int> s2 = s1;
  EXPECT_EQ(s1.top(), s2.top());
}
TEST(StackTests, Test13) {
  Stack<int> s1{1, 2, 3, 4, 5, 6};
  Stack<int> s2 = std::move(s1);
  EXPECT_EQ(s2.top(), 6);
  EXPECT_EQ(s1.empty(), true);
}
TEST(StackTests, Test14) {
  Stack<int> s1{1, 2, 3, 4, 5, 6};
  Stack<int> s2 = {7, 8, 9, 10};

  s1.swap(s2);
  EXPECT_EQ(s1.top(), 10);
  EXPECT_EQ(s2.top(), 6);
}
TEST(StackTests, Test15) {
  Stack<int> s1{1, 2, 3, 4, 5, 6};
  Stack<int> s2;
  s2 = std::move(s1);
  EXPECT_EQ(s2.top(), 6);
}
TEST(StackTests, Test16) {
  s21::Stack<int> stack;
  stack.insert_many_back(42);

  ASSERT_EQ(stack.size(), 1);
  EXPECT_EQ(stack.top(), 42);
}

TEST(StackTests, Test17) {
  s21::Stack<int> stack;
  stack.insert_many_back(1, 2, 3, 4);

  ASSERT_EQ(stack.size(), 4);
  EXPECT_EQ(stack.top(), 4);

  stack.pop();
  EXPECT_EQ(stack.top(), 3);

  stack.pop();
  EXPECT_EQ(stack.top(), 2);
}

TEST(StackTests, Test18) {
  s21::Stack<int> stack;
  stack.push(10);
  stack.insert_many_back(20, 30);

  ASSERT_EQ(stack.size(), 3);

  EXPECT_EQ(stack.top(), 30);
  stack.pop();
  EXPECT_EQ(stack.top(), 20);
  stack.pop();
  EXPECT_EQ(stack.top(), 10);
}

TEST(StackTests, Test19) {
  s21::Stack<std::string> stack;
  stack.insert_many_back("hello", "world");

  ASSERT_EQ(stack.size(), 2);
  EXPECT_EQ(stack.top(), "world");

  stack.pop();
  EXPECT_EQ(stack.top(), "hello");
}

}  // namespace s21