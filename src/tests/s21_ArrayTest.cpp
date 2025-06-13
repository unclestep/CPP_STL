#include "s21_test.h"

namespace s21 {

TEST(ArrayTests, Test1) { Array<int, 4> newArray; }

TEST(ArrayTests, Test2) {
  Array<int, 4> newArray{1, 2, 3, 4};
  std::array<int, 5> ar{1, 2, 3};
  auto s1 = ar.begin();
  EXPECT_EQ(*s1, 1);
  auto s = newArray.begin();
  auto s2 = newArray.end();
  EXPECT_EQ(*s, 1);
  EXPECT_EQ(*s2, 4);
}

TEST(ArrayTests, Test3) {
  Array<int, 4> original{1, 2, 3, 4};
  Array<int, 4> copy(original);

  EXPECT_EQ(original.size(), copy.size());
  for (size_t i = 0; i < original.size(); ++i) {
    EXPECT_EQ(original[i], copy[i]);
  }
}
TEST(ArrayTests, Test4) {
  Array<int, 4> original{1, 2, 3, 4};
  Array<int, 4> moved(std::move(original));

  EXPECT_EQ(moved.size(), 4u);
  EXPECT_EQ(original.size(), 4u);
}
TEST(ArrayTests, Test5) {
  Array<int, 0> empty_arr;
  EXPECT_TRUE(empty_arr.empty());

  Array<int, 3> non_empty_arr;
  EXPECT_FALSE(non_empty_arr.empty());
}
TEST(ArrayTests, Test6) {
  Array<int, 5> arr;
  EXPECT_EQ(arr.size(), 5u);

  Array<int, 0> empty_arr;
  EXPECT_EQ(empty_arr.size(), 0u);
}
TEST(ArrayTests, Test7) {
  Array<int, 7> arr;
  EXPECT_EQ(arr.max_size(), 7u);

  Array<double, 100> large_arr;
  EXPECT_EQ(large_arr.max_size(), 100);
}
TEST(ArrayTests, Test8) {
  Array<int, 4> arr{10, 20, 30, 40};
  EXPECT_EQ(arr[0], 10);
  EXPECT_EQ(arr[3], 40);
}
TEST(ArrayTests, Test9) {
  Array<int, 4> source{1, 2, 3, 4};
  Array<int, 4> dest;

  dest = std::move(source);

  for (size_t i = 0; i < dest.size(); ++i) {
    EXPECT_EQ(dest[i], i + 1);
  }
}
TEST(ArrayTests, Test10) {
  Array<std::string, 2> source{"hello", "world"};
  Array<std::string, 2> dest;

  dest = std::move(source);

  EXPECT_EQ(dest[0], "hello");
  EXPECT_EQ(dest[1], "world");

  EXPECT_TRUE(source[0].empty() || source[0] == "hello");
  EXPECT_TRUE(source[1].empty() || source[1] == "world");
}

TEST(ArrayTests, Test11) {
  Array<int, 3> arr = {10, 20, 30};
  int *ptr = arr.data();

  EXPECT_EQ(*ptr, 10);
  EXPECT_EQ(*(ptr + 1), 20);
  EXPECT_EQ(*(ptr + 2), 30);
}

TEST(ArrayTests, Test12) {
  Array<int, 4> arr = {1, 2, 3, 4};
  EXPECT_EQ(arr.back(), 4);

  Array<std::string, 2> str_arr = {"hello", "world"};
  EXPECT_EQ(str_arr.back(), "world");
}

TEST(ArrayTests, Test13) {
  Array<int, 4> arr = {1, 2, 3, 4};
  EXPECT_EQ(arr.front(), 1);

  Array<std::string, 2> str_arr = {"hello", "world"};
  EXPECT_EQ(str_arr.front(), "hello");
}

TEST(ArrayTests, Test14) {
  Array<int, 3> arr = {5, 10, 15};
  EXPECT_EQ(arr.at(0), 5);
  EXPECT_EQ(arr.at(2), 15);
}

TEST(ArrayTests, Test15) {
  Array<int, 2> arr = {1, 2};
  EXPECT_THROW(arr.at(2), std::out_of_range);
  EXPECT_THROW(arr.at(100), std::out_of_range);
}

TEST(ArrayTests, Test16) {
  Array<int, 3> arr1 = {1, 2, 3};
  Array<int, 3> arr2 = {4, 5, 6};

  arr1.swap(arr2);

  EXPECT_EQ(arr1[0], 4);
  EXPECT_EQ(arr1[1], 5);
  EXPECT_EQ(arr1[2], 6);

  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
}

TEST(ArrayTests, Test17) {
  Array<int, 3> arr = {1, 2, 3};
  arr.swap(arr);

  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
}

TEST(ArrayTests, Test18) {
  Array<int, 3> arr = {7, 8, 9};
  EXPECT_EQ(arr.back(), 9);
  EXPECT_EQ(arr.front(), 7);
}
TEST(ArrayTests, Test19) {
  Array<int, 5> arr;
  arr.fill(42);

  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], 42);
  }
}

TEST(ArrayTests, Test20) {
  Array<std::string, 3> arr;
  arr.fill("hello");

  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], "hello");
  }
}

TEST(ArrayTests, Test21) {
  Array<int, 0> empty_arr;
  EXPECT_NO_THROW(
      empty_arr.fill(100));  // Не должно быть ошибок на пустом массиве
}

TEST(ArrayTests, Test22) {
  Array<int, 4> arr = {1, 2, 3, 4};
  arr.fill(0);

  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], 0);
  }
}

TEST(ArrayTests, Test23) {
  const int value = 7;
  Array<int, 3> arr;
  arr.fill(value);

  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], value);
  }
}

}  // namespace s21
