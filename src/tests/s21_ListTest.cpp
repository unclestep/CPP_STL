//
// Created by Valentine on 05.05.2025.
//
#include "s21_test.h"

namespace s21 {
TEST(ListTests, Test1) {
  List<int> newList;

  newList.push_back(30);
  auto iterator = newList.begin();
  EXPECT_EQ(*iterator, 30);
  ++iterator;
  EXPECT_EQ(iterator, nullptr);
}
TEST(ListTests, Test2) {
  List<int> newList;

  newList.push_back(30);
  newList.push_back(20);
  newList.push_back(10);
  newList.push_back(0);
  newList.push_back(-10);
  newList.push_back(-20);
  newList.push_back(-30);
  newList.push_back(-40);
  newList.push_back(-50);
  int ch = 30;
  for (auto it = newList.begin(); it != nullptr; ++it) {
    EXPECT_EQ(*it, ch);
    ch -= 10;
  }
}
TEST(ListTests, Test3) {
  List<int> newList;

  newList.push_back(30);
  newList.push_back(20);
  newList.push_back(10);
  newList.push_back(0);
  newList.push_front(40);
  int ch = 40;
  for (auto it = newList.begin(); it != nullptr; ++it) {
    EXPECT_EQ(*it, ch);
    ch -= 10;
  }
}
TEST(ListTests, Test4) {
  List<int> newList;

  newList.push_back(30);
  newList.push_back(20);
  newList.pop_back();
  auto it = newList.end();
  EXPECT_EQ(*it, 30);
}
TEST(ListTests, Test5) {
  List<int> newList;
  newList.push_back(30);
  newList.push_back(20);
  newList.pop_back();

  auto it = newList.end();
  EXPECT_EQ(*it, 30);
}
TEST(ListTests, Test6) {
  List<int> newList;
  newList.push_back(30);
  newList.push_back(40);
  newList.push_back(50);
  newList.push_back(60);
  EXPECT_EQ(newList.size(), 4);
}
TEST(ListTests, Test7) {
  List<int> newList;

  EXPECT_EQ(newList.size(), 0);
}
TEST(ListTests, Test8) {
  List<int> newList;

  EXPECT_EQ(newList.empty(), true);
}
TEST(ListTests, Test9) {
  List<int> newList;

  EXPECT_EQ(std::numeric_limits<std::size_t>::max() / sizeof(int),
            newList.max_size());
}
TEST(ListTests, Test10) {
  List<int> newList{1, 2, 3, 4, 5};

  int checkList = 1;
  for (auto it = newList.begin(); it != nullptr; ++it) {
    EXPECT_EQ(*it, checkList);
    ++checkList;
  }
}
TEST(ListTests, Test11) {
  List<int> newList{1, 2, 3, 5, 6, 7, 8};

  EXPECT_EQ(*(newList.insert(newList.begin(), 0)), 0);
}
TEST(ListTests, Test12) {
  List<int> newList{1, 2, 3, 5, 6, 7, 8};

  EXPECT_EQ(*(newList.insert(newList.end(), 9)), 9);
}
TEST(ListTests, Test13) {
  List<int> newList{1, 2, 4, 5, 6, 7, 8};

  auto it = newList.begin();
  ++it;
  ++it;

  EXPECT_EQ(*(newList.insert(it, 3)), 3);

  int check = 1;

  for (auto it = newList.begin(); it != newList.end(); ++it) {
    EXPECT_EQ(*it, check);
    check++;
  }
}
TEST(ListTests, Test14) {
  List<int> newList{1, 2, 4, 5, 6, 7, 8};

  newList.clear();

  EXPECT_EQ(newList.begin(), nullptr);
}
TEST(ListTests, Test15) {
  size_t num = 15;
  List<int> newList(num);

  EXPECT_EQ(newList.size(), num);

  for (auto it = newList.begin(); it != newList.end(); ++it) {
    EXPECT_EQ(*it, 0);
  }
}
TEST(ListTests, Test16) {
  List<int> newList{1, 2, 3, 4, 5, 6, 7, 8};

  List<int> copyList(newList);
  int counter = 1;
  for (auto it = copyList.begin(); it != copyList.end(); ++it) {
    EXPECT_EQ(*it, counter);
    counter++;
  }
}
TEST(ListTests, Test17) {
  List<int> newList{1, 2, 3, 4, 5, 6, 7, 8};

  List<int> movedList = std::move(newList);
  int counter = 1;
  for (auto it = movedList.begin(); it != movedList.end(); ++it) {
    EXPECT_EQ(*it, counter);
    counter++;
  }
  EXPECT_EQ(newList.begin(), nullptr);
}
TEST(ListTests, Test18) {
  List<int> newList{1, 2, 3, 4, 5, 6, 7, 8};

  auto it = newList.begin();

  ++it;
  ++it;

  newList.erase(it);

  auto newIt = newList.begin();
  ++newIt;
  ++newIt;

  EXPECT_EQ(*newIt, 4);
}
TEST(ListTests, Test19) {
  List<int> newList{1, 2, 3, 4, 5, 6, 7, 8};

  EXPECT_EQ(newList.front(), 1);
  EXPECT_EQ(newList.back(), 8);
}
TEST(ListTests, Test20) {
  List<int> newList1{1, 2, 3, 4, 5, 6, 7, 8};
  List<int> newList2{10, 11, 12};

  newList1.swap(newList2);

  EXPECT_EQ(newList1.front(), 10);
  EXPECT_EQ(newList1.back(), 12);
  EXPECT_EQ(newList2.front(), 1);
  EXPECT_EQ(newList2.back(), 8);
}
TEST(ListTests, Test21) {
  List<int> newList1{8, 7, 6, 5, 4, 3, 2, 1};

  newList1.sort();

  EXPECT_EQ(newList1.front(), 1);
  EXPECT_EQ(newList1.back(), 8);
}
TEST(ListTests, Test22) {
  List<int> list1 = {5, 9, 1, 3, 3};
  List<int> list2 = {8, 7, 2, 3, 4, 4};

  list1.sort();
  list2.sort();
  list1.merge(list2);

  EXPECT_EQ(list1.front(), 1);
  EXPECT_EQ(list1.back(), 9);
}
TEST(ListTests, Test23) {
  List<int> list1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  list1.reverse();

  EXPECT_EQ(list1.front(), 9);
  EXPECT_EQ(list1.back(), 1);
}
TEST(ListTests, Test24) {
  List<int> list1 = {1, 2, 2, 2, 2, 2, 3};

  list1.unique();

  EXPECT_EQ(list1.front(), 1);
  EXPECT_EQ(list1.back(), 3);
}
TEST(ListTests, Test25) {
  List<int> list1 = {4, 5, 6};
  List<int> list2 = {1, 2};

  list1.splice(list1.cbegin(), list2);

  for (auto it = list1.begin(); it != nullptr; ++it) {
    std::cout << "It == " << *it << "\n";
  }
}
TEST(ListTests, Test26) {
  List<int> list1 = {4, 5, 6};
  List<int> list2 = {1, 2};

  list1.splice(list1.cend(), list2);

  for (auto it = list1.begin(); it != nullptr; ++it) {
    std::cout << "It == " << *it << "\n";
  }
}
TEST(ListTests, Test27) {
  List<int> list1 = {4, 5, 6};
  List<int> list2 = {1, 2};

  auto cit = list1.cbegin();
  ++cit;
  list1.splice(cit, list2);

  for (auto it = list1.begin(); it != nullptr; ++it) {
    std::cout << "It == " << *it << "\n";
  }
}
TEST(ListTests, Test28) {
  s21::List<int> list;
  list.insert_many_back(42);

  ASSERT_EQ(list.size(), 1);
  EXPECT_EQ(list.front(), 42);
  EXPECT_EQ(list.back(), 42);
}

TEST(ListTests, Test29) {
  s21::List<int> list;
  list.insert_many_back(1, 2, 3, 4, 5);

  ASSERT_EQ(list.size(), 5);

  int expected = 1;
  for (auto it = list.begin(); it != nullptr; ++it, ++expected) {
    EXPECT_EQ(*it, expected);
  }
}

TEST(ListTests, Test30) {
  s21::List<int> list;
  list.push_back(100);
  list.insert_many_back(200, 300, 400);

  ASSERT_EQ(list.size(), 4);

  int expected_values[] = {100, 200, 300, 400};
  int i = 0;
  for (auto it = list.begin(); it != nullptr; ++it, ++i) {
    EXPECT_EQ(*it, expected_values[i]);
  }
}

TEST(ListTests, Test31) {
  s21::List<std::string> list;
  list.insert_many_back("one", "two", "three");

  ASSERT_EQ(list.size(), 3);

  std::string expected_values[] = {"one", "two", "three"};
  int i = 0;
  for (auto it = list.begin(); it != nullptr; ++it, ++i) {
    EXPECT_EQ(*it, expected_values[i]);
  }
}
TEST(ListTests, Test32) {
  s21::List<int> list;
  list.insert_many_front(5);

  ASSERT_EQ(list.size(), 1);
  EXPECT_EQ(list.front(), 5);
  EXPECT_EQ(list.back(), 5);
}

TEST(ListTests, Test33) {
  s21::List<int> list;
  list.insert_many_front(1, 2, 3);

  ASSERT_EQ(list.size(), 3);
  EXPECT_EQ(list.front(), 3);
  EXPECT_EQ(list.back(), 1);

  auto it = list.begin();
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 1);
}

TEST(ListTests, Test34) {
  s21::List<int> list;
  list.push_back(10);
  list.insert_many_front(20, 30);

  ASSERT_EQ(list.size(), 3);
  EXPECT_EQ(list.front(), 30);
  EXPECT_EQ(list.back(), 10);

  auto it = list.begin();
  EXPECT_EQ(*it, 30);
  ++it;
  EXPECT_EQ(*it, 20);
  ++it;
  EXPECT_EQ(*it, 10);
}

TEST(ListTests, Test35) {
  s21::List<std::string> list;
  list.insert_many_front("one", "two", "three");

  ASSERT_EQ(list.size(), 3);
  EXPECT_EQ(list.front(), "three");
  EXPECT_EQ(list.back(), "one");

  auto it = list.begin();
  EXPECT_EQ(*it, "three");
  ++it;
  EXPECT_EQ(*it, "two");
  ++it;
  EXPECT_EQ(*it, "one");
}
TEST(ListTests, Test36) {
  List<int> lst = {2, 3, 4};
  auto pos = lst.begin();  // указывает на элемент 2

  lst.insert_many(pos, 100, 200);

  auto it = lst.begin();
  EXPECT_EQ(*it, 100);
  ++it;
  EXPECT_EQ(*it, 200);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
  ++it;
  EXPECT_EQ(it, nullptr);
}

TEST(ListTests, Test37) {
  List<int> lst = {1, 2, 5, 6};
  auto pos = lst.begin();
  ++pos;
  ++pos;  // указывает на 5

  lst.insert_many(pos, 100, 101);

  auto it = lst.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 100);
  ++it;
  EXPECT_EQ(*it, 101);
  ++it;
  EXPECT_EQ(*it, 5);
  ++it;
  EXPECT_EQ(*it, 6);
  ++it;
  EXPECT_EQ(it, nullptr);
}

TEST(ListTests, Test38) {
  List<int> lst = {1, 2, 3};
  auto pos = lst.end();
  lst.insert_many(pos, 10, 11);

  auto it = lst.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 10);
  ++it;
  EXPECT_EQ(*it, 11);
  ++it;
  EXPECT_EQ(*it, 3);
}

}  // namespace s21