//
// Created by rasko on 31.03.2025.
//
#include "s21_test.h"
namespace s21 {

TEST(VectorTests, Test1) {
  Vector<int> v = {1, 2, 3, 4, 5};
  int counter = 1;
  for (Vector<int>::iterator it = v.begin(); it != v.end(); it++) {
    EXPECT_EQ(counter, *it);
    counter++;
  }
}

TEST(VectorTests, Test2) {
  Vector<double> v = {1.0, 2.0, 3.0, 4.0, 5.0};
  int counter = 1.0;
  for (Vector<double>::iterator it = v.begin(); it != v.end(); it++) {
    EXPECT_EQ(counter, *it);
    counter++;
  }
}

TEST(VectorTests, Test3) {
  Vector<double> v = {1.0, 2.0, 3.0, 4.0, 5.0};
  int counter = 1.0;
  v.push_back(6.0);
  for (Vector<double>::iterator it = v.begin(); it != v.end(); it++) {
    EXPECT_EQ(counter, *it);
    counter++;
  }
}

TEST(VectorTests, Test4) {
  Vector<double> v = {1.0, 2.0, 3.0, 4.0, 5.0};
  std::vector<double> v1 = {1.0, 2.0, 3.0, 4.0, 5.0};
  v.push_back(6.0);
  v1.push_back(6.0);
  EXPECT_EQ(v.at(2), v1.at(2));
}

TEST(VectorTests, Test5) {
  Vector<int> v = {1, 2, 3, 4, 5};
  v.push_back(6);
  Vector<int> v1;
  v1 = std::move(v);
  v1.at(2);
  EXPECT_EQ(v1.at(2), 3);
}

TEST(VectorTests, Test6) {
  Vector<int> v = {1, 2, 3, 4, 5};
  v.push_back(6);
  EXPECT_EQ(v[0], 1);
}
TEST(VectorTests, Test7) {
  Vector<int> v = {1, 2, 3, 4, 5};
  v.push_back(6);
  v.push_back(7);
  EXPECT_EQ(v.front(), 1);
}
TEST(VectorTests, Test8) {
  Vector<int> v = {1, 2, 3, 4, 5};
  v.push_back(6);
  EXPECT_EQ(v.back(), 6);
}
TEST(VectorTests, Test9) {
  Vector<int> v = {1, 2, 3, 4, 5};
  v.push_back(6);
  EXPECT_EQ(*v.data(), 1);
}
TEST(VectorTests, Test10) {
  Vector<int> v = {1, 2, 3, 4, 5};
  v.push_back(6);
  EXPECT_EQ(v.empty(), false);
}
TEST(VectorTests, Test11) {
  Vector<int> v = {};
  EXPECT_EQ(v.empty(), true);
}
TEST(VectorTests, Test12) {
  Vector<int> v = {1};
  EXPECT_EQ(v.empty(), false);
}

TEST(VectorTests, Test13) {
  Vector<int> v = {1};
  std::vector<int> vorg;
  EXPECT_EQ(vorg.max_size(), v.max_size());
}

TEST(VectorTests, Test14) {
  Vector<double> v = {1};
  std::vector<double> vorg;
  EXPECT_EQ(vorg.max_size(), v.max_size());
}

TEST(VectorTests, Test15) {
  Vector<int> v = {1};
  EXPECT_EQ(*v.data(), v[0]);
}
TEST(VectorTests, Test16) {
  Vector<char> v = {'a'};
  std::vector<char> vorg;
  EXPECT_EQ(vorg.max_size(), v.max_size());
}
TEST(VectorTests, Test17) {
  Vector<int> v{5, 12, 13, 14};
  v.push_back(12);
  std::vector<int> vorg{1, 2, 3, 4};
  vorg.push_back(10);
  EXPECT_EQ(vorg.capacity(), v.capacity());
}
TEST(VectorTests, Test18) {
  Vector<int> v{5, 12, 13, 14};
  std::vector<int> v1{5, 12, 13, 14};
  v.push_back(12);
  v1.push_back(12);
  v.shrink_to_fit();
  v1.shrink_to_fit();
  EXPECT_EQ(v1.capacity(), v.capacity());
}

TEST(VectorTests, Test19) {
  std::vector<int> v1{5, 12, 13, 14};
  Vector<int> v{5, 12, 13, 14};
  v1.reserve(2);
  v.reserve(2);
  EXPECT_EQ(v1.capacity(), v.capacity());
}
TEST(VectorTests, Test20) {
  std::vector<int> v1{5, 12, 13, 14};
  Vector<int> v{5, 12, 13, 14};
  v1.reserve(17);
  v.reserve(17);
  EXPECT_EQ(v1.capacity(), v.capacity());
}

TEST(VectorTests, Test21) {
  std::vector<int> v1{5, 12, 13, 14};
  Vector<int> v{5, 12, 13, 14};
  v1.erase(v1.begin());
  v.erase(v.begin());

  EXPECT_EQ(v1.size(), v.size());
  EXPECT_EQ(v[0], v1[0]);
}

TEST(VectorTests, Test22) {
  Vector<int> v{5, 12, 13, 14};

  v.insert(v.begin(), 7);

  EXPECT_EQ(*(v.begin()), 7);
}

TEST(VectorTests, Test23) {
  Vector<int> v{5, 12, 13, 14};

  v.pop_back();

  EXPECT_EQ(*(v.end() - 1), 13);
}

TEST(VectorTests, Test24) {
  Vector<int> v1{5, 12, 13, 14};
  Vector<int> v2{17, 2};
  v1.swap(v2);

  EXPECT_EQ(5, *(v2.begin()));
  EXPECT_EQ(17, *(v1.begin()));
}

TEST(VectorTests, Test25) {
  Vector<int> v1{5, 12, 13, 14};
  Vector<int> v2;
  v2 = std::move(v1);

  EXPECT_EQ(14, v2.back());
}

TEST(VectorTests, Test26) {
  Vector<int> v1{5, 12, 13, 14};
  Vector<int> v2(v1);

  EXPECT_EQ(14, v2.back());
  EXPECT_EQ(14, v1.back());
}
TEST(VectorTests, Test27) {
  s21::Vector<int> v;
  v.insert_many_back(42);
  ASSERT_EQ(v.size(), 1);
  EXPECT_EQ(v[0], 42);
}

TEST(VectorTests, Test28) {
  s21::Vector<int> v;
  v.insert_many_back(1, 2, 3, 4, 5);
  ASSERT_EQ(v.size(), 5);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[3], 4);
  EXPECT_EQ(v[4], 5);
}

TEST(VectorTests, Test29) {
  s21::Vector<double> v;
  v.insert_many_back(1, 2.5f, 3.14);
  ASSERT_EQ(v.size(), 3);
  EXPECT_DOUBLE_EQ(v[0], 1.0);
  EXPECT_DOUBLE_EQ(v[1], 2.5);
  EXPECT_DOUBLE_EQ(v[2], 3.14);
}

TEST(VectorTests, Test30) {
  s21::Vector<int> v;
  v.insert_many_back();
  EXPECT_EQ(v.size(), 0);
}
TEST(VectorTests, Test31) {
  Vector<int> vec = {3, 4, 5};
  auto it = vec.begin();
  vec.insert_many(it, 1, 2);

  ASSERT_EQ(vec.size(), 5u);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
  EXPECT_EQ(vec[4], 5);
}

TEST(VectorTests, Test32) {
  Vector<int> vec = {1, 2, 6, 7};
  auto it = vec.begin() + 2;
  vec.insert_many(it, 3, 4, 5);

  ASSERT_EQ(vec.size(), 7u);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
  EXPECT_EQ(vec[4], 5);
  EXPECT_EQ(vec[5], 6);
  EXPECT_EQ(vec[6], 7);
}

TEST(VectorTests, Test33) {
  Vector<int> vec = {1, 2, 3};
  auto it = vec.end();
  vec.insert_many(it, 4, 5);

  ASSERT_EQ(vec.size(), 5u);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
  EXPECT_EQ(vec[4], 5);
}

TEST(VectorTests, Test34) {
  Vector<int> vec;
  vec.insert_many(vec.begin(), 10, 20, 30);

  ASSERT_EQ(vec.size(), 3u);
  EXPECT_EQ(vec[0], 10);
  EXPECT_EQ(vec[1], 20);
  EXPECT_EQ(vec[2], 30);
}

}  // namespace s21
