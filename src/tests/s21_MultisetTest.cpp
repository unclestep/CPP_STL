#include "s21_test.h"

namespace s21 {
TEST(MultisetTest, DefaultConstructor) {
  multiset<int> ms;
  EXPECT_TRUE(ms.empty());
}

TEST(MultisetTest, InitializerListConstructor) {
  multiset<int> ms = {1, 2, 3, 4};

  EXPECT_EQ(ms.size(), 4U);
  EXPECT_TRUE(ms.contains(1));
  EXPECT_TRUE(ms.contains(2));
  EXPECT_TRUE(ms.contains(3));
  EXPECT_TRUE(ms.contains(4));
}

TEST(MultisetTest, RepeatedInitializerListConstructor) {
  multiset<int> ms = {1, 1, 2, 2};

  EXPECT_EQ(ms.size(), 4U);
  EXPECT_EQ(ms.count(1), 2U);
  EXPECT_EQ(ms.count(2), 2U);
}

TEST(MultisetTest, CopyConstructor) {
  multiset<int> ms1 = {1, 2, 3, 4};

  multiset<int> ms2 = ms1;

  EXPECT_EQ(ms1.size(), ms2.size());
  EXPECT_TRUE(std::equal(ms1.begin(), ms1.end(), ms2.begin(), ms2.end()));
}

TEST(MultisetTest, MoveConstructor) {
  multiset<int> ms1 = {1, 2, 3, 4};

  multiset<int> ms2 = std::move(ms1);

  EXPECT_EQ(ms1.size(), 0U);
  EXPECT_EQ(ms2.size(), 4U);
  EXPECT_EQ(ms1.begin(), ms1.end());
  EXPECT_TRUE(ms2.contains(1));
  EXPECT_TRUE(ms2.contains(2));
  EXPECT_TRUE(ms2.contains(3));
  EXPECT_TRUE(ms2.contains(4));
}

TEST(MultisetTest, CopyAssignment) {
  multiset<int> ms1 = {1, 2, 3, 4};

  multiset<int> ms2;
  ms2 = ms1;

  EXPECT_EQ(ms1.size(), ms2.size());
  EXPECT_TRUE(std::equal(ms1.begin(), ms1.end(), ms2.begin(), ms2.end()));
}

TEST(MultisetTest, MoveAssignment) {
  multiset<int> ms1 = {1, 2, 3, 4};

  multiset<int> ms2;
  ms2 = std::move(ms1);

  EXPECT_EQ(ms1.size(), 0U);
  EXPECT_EQ(ms2.size(), 4U);
  EXPECT_EQ(ms1.begin(), ms1.end());
  EXPECT_TRUE(ms2.contains(1));
  EXPECT_TRUE(ms2.contains(2));
  EXPECT_TRUE(ms2.contains(3));
  EXPECT_TRUE(ms2.contains(4));
}

TEST(MultisetTest, MaxSize) {
  multiset<int> ms = {1, 2, 3, 4};
  EXPECT_GT(ms.max_size(), ms.size());
}

TEST(MultisetTest, ClearEmpty) {
  multiset<int> ms;
  ms.clear();
  EXPECT_EQ(ms.size(), 0U);
  EXPECT_EQ(ms.begin(), ms.end());
}

TEST(MultisetTest, ClearNonEmpty) {
  multiset<int> ms = {1, 2, 3, 4, 5};
  ms.clear();
  EXPECT_EQ(ms.size(), 0U);
  EXPECT_EQ(ms.begin(), ms.end());
}

TEST(MultisetTest, Insert1) {
  multiset<int> ms;
  ms.insert(1);

  EXPECT_EQ(ms.size(), 1U);
  EXPECT_TRUE(ms.contains(1));
}

TEST(MultisetTest, Insert2) {
  multiset<int> ms = {1, 10, 20};
  ms.insert(5);

  EXPECT_EQ(ms.size(), 4U);
  EXPECT_TRUE(ms.contains(5));
}

TEST(MultisetTest, Insert3) {
  multiset<int> ms;
  for (int i = -10; i <= 10; ++i) {
    ms.insert(i);
  }

  EXPECT_EQ(ms.size(), 21U);

  int exp = -10;
  for (auto it = ms.begin(); it != ms.end(); ++it, ++exp) {
    EXPECT_EQ(*it, exp);
  }
}

TEST(MultisetTest, Insert4) {
  multiset<int> ms;
  for (int i = 10; i >= -10; --i) {
    ms.insert(i);
  }

  EXPECT_EQ(ms.size(), 21U);

  int exp = 10;
  for (auto it = --ms.end();; --it, --exp) {
    EXPECT_EQ(*it, exp);
    if (it == ms.begin()) break;
  }
}

TEST(MultisetTest, Insert5) {
  multiset<int> ms;
  for (int i = 0; i <= 1000; ++i) {
    ms.insert(i);
  }

  EXPECT_EQ(ms.size(), 1001U);

  int exp = 0;
  for (auto it = ms.begin(); it != ms.end(); ++it, ++exp) {
    EXPECT_EQ(*it, exp);
  }
}

TEST(MultisetTest, InsertDuplicates) {
  multiset<int> ms;
  for (int i = 1; i <= 1000; ++i) {
    auto res = ms.insert(i % 10);
  }

  EXPECT_EQ(ms.size(), 1000U);

  for (int j = 0; j <= 9; ++j) {
    EXPECT_EQ(ms.count(j), 100U);
  }

  int exp = 0, count = 0;
  for (auto it = ms.begin(); it != ms.end(); ++it) {
    EXPECT_EQ(*it, exp);
    ++count;
    if (count == 100) {
      ++exp;
      count = 0;
    }
  }
}

TEST(MultisetTest, InsertAfterClear1) {
  multiset<int> ms = {0, 21, 42};
  ms.clear();
  ms.insert(1);
  EXPECT_EQ(ms.size(), 1U);
  EXPECT_TRUE(ms.contains(1));
}

TEST(MultisetTest, InsertAfterClear2) {
  multiset<int> ms = {0, 21, 42};
  ms.clear();
  ms.insert(21);
  EXPECT_EQ(ms.size(), 1U);
  EXPECT_TRUE(ms.contains(21));
}

TEST(MultisetTest, Erase1) {
  multiset<int> ms = {1, 2, 3, 4, 5};
  auto it = ms.find(1);
  ms.erase(it);
  EXPECT_EQ(ms.size(), 4U);
  EXPECT_FALSE(ms.contains(1));
  EXPECT_TRUE(ms.contains(2));
  EXPECT_TRUE(ms.contains(3));
  EXPECT_TRUE(ms.contains(4));
  EXPECT_TRUE(ms.contains(5));
}

TEST(MultisetTest, Erase2) {
  multiset<int> ms = {1, 2, 3, 4, 5};
  auto it = ms.find(5);
  ms.erase(it);
  EXPECT_EQ(ms.size(), 4U);
  EXPECT_FALSE(ms.contains(5));
  EXPECT_TRUE(ms.contains(4));
  EXPECT_TRUE(ms.contains(3));
  EXPECT_TRUE(ms.contains(2));
  EXPECT_TRUE(ms.contains(1));
}

TEST(MultisetTest, Erase3) {
  multiset<int> ms = {1, 2, 3, 4, 5};
  auto it = ms.find(3);
  ms.erase(it);
  EXPECT_EQ(ms.size(), 4U);
  EXPECT_FALSE(ms.contains(3));
  EXPECT_TRUE(ms.contains(1));
  EXPECT_TRUE(ms.contains(2));
  EXPECT_TRUE(ms.contains(4));
  EXPECT_TRUE(ms.contains(5));
}

TEST(MultisetTest, EraseUnexisted) {
  multiset<int> ms = {1, 2, 3, 4, 5};
  auto it = ms.find(6);
  ms.erase(it);
  EXPECT_EQ(ms.size(), 5U);
  EXPECT_TRUE(ms.contains(1));
  EXPECT_TRUE(ms.contains(2));
  EXPECT_TRUE(ms.contains(3));
  EXPECT_TRUE(ms.contains(4));
  EXPECT_TRUE(ms.contains(5));
}

TEST(MultisetTest, EraseBegin) {
  multiset<int> ms;
  auto it = ms.begin();
  ms.erase(it);
  EXPECT_EQ(ms.size(), 0U);
  EXPECT_EQ(ms.begin(), ms.end());
}

TEST(MultisetTest, EraseEnd) {
  multiset<int> ms;
  auto it = ms.end();
  ms.erase(it);
  EXPECT_EQ(ms.size(), 0U);
  EXPECT_EQ(ms.begin(), ms.end());
}

TEST(MultisetTest, EraseAll) {
  multiset<int> ms;
  for (int i = 0; i <= 1000; ++i) {
    ms.insert(i);
  }
  while (!ms.empty()) {
    ms.erase(ms.begin());
  }
  EXPECT_EQ(ms.size(), 0U);
  EXPECT_EQ(ms.begin(), ms.end());
}

TEST(MultisetTest, EraseOdd) {
  multiset<int> ms;
  for (int i = 1; i <= 21; ++i) {
    ms.insert(i);
  }
  for (int j = 1; j <= 21; j += 2) {
    auto it = ms.find(j);
    ms.erase(it);
  }
  EXPECT_EQ(ms.size(), 10U);
  for (int z = 2; z <= 20; z += 2) {
    EXPECT_TRUE(ms.contains(z));
  }
  for (int w = 1; w <= 21; w += 2) {
    EXPECT_FALSE(ms.contains(w));
  }
}

TEST(MultisetTest, EraseSingle) {
  multiset<int> ms = {21};
  auto it = ms.begin();
  ms.erase(it);
  EXPECT_EQ(ms.size(), 0U);
  EXPECT_EQ(ms.begin(), ms.end());
}

TEST(MultisetTest, InsertManyEmptySet) {
  multiset<int> ms;
  auto results = ms.insert_many(1, 2, 3, 4, 5);
  EXPECT_EQ(ms.size(), 5U);
  EXPECT_TRUE(ms.contains(1));
  EXPECT_TRUE(ms.contains(2));
  EXPECT_TRUE(ms.contains(3));
  EXPECT_TRUE(ms.contains(4));
  EXPECT_TRUE(ms.contains(5));
  for (const auto &pair : results) {
    EXPECT_TRUE(pair.second);
  }
}

TEST(MultisetTest, InsertManyNonEmptySet) {
  multiset<int> ms = {0};
  auto results = ms.insert_many(1, 2, 3, 4, 5);
  EXPECT_EQ(ms.size(), 6U);
  EXPECT_TRUE(ms.contains(0));
  EXPECT_TRUE(ms.contains(1));
  EXPECT_TRUE(ms.contains(2));
  EXPECT_TRUE(ms.contains(3));
  EXPECT_TRUE(ms.contains(4));
  EXPECT_TRUE(ms.contains(5));
  for (const auto &pair : results) {
    EXPECT_TRUE(pair.second);
  }
}

TEST(MultisetTest, InsertManyWithDuplicates) {
  multiset<int> ms;
  auto results = ms.insert_many(1, 2, 1, 2, 5);

  EXPECT_EQ(ms.size(), 5U);

  EXPECT_EQ(ms.count(1), 2U);
  EXPECT_EQ(ms.count(2), 2U);
  EXPECT_EQ(ms.count(5), 1U);
}

TEST(MultisetTest, InsertManyInDuplicates1) {
  multiset<int> ms = {1, 2, 1, 2, 5};
  ms.insert_many(1, 2, 1, 2, 5);

  EXPECT_EQ(ms.size(), 10U);

  EXPECT_EQ(ms.count(1), 4U);
  EXPECT_EQ(ms.count(2), 4U);
  EXPECT_EQ(ms.count(5), 2U);
}

TEST(MultisetTest, InsertManyInDuplicates2) {
  multiset<int> ms = {1, 2, 1, 2, 5};
  ms.insert_many(1, 2, 1, 2, 5, 6);

  EXPECT_EQ(ms.size(), 11U);

  EXPECT_EQ(ms.count(1), 4U);
  EXPECT_EQ(ms.count(2), 4U);
  EXPECT_EQ(ms.count(5), 2U);
  EXPECT_EQ(ms.count(6), 1U);
}

TEST(MultisetTest, InsertManyNothing1) {
  multiset<int> ms = {21};
  auto results = ms.insert_many();
  EXPECT_EQ(ms.size(), 1U);
  EXPECT_TRUE(ms.contains(21));
  EXPECT_TRUE(results.empty());
}

TEST(MultisetTest, InsertManyNothing2) {
  multiset<int> ms;
  auto results = ms.insert_many();
  EXPECT_TRUE(ms.empty());
  EXPECT_TRUE(results.empty());
}

TEST(MultisetTest, MergeEmptySet1) {
  multiset<int> ms1 = {1, 2, 3};
  multiset<int> ms2;
  ms1.merge(ms2);
  EXPECT_EQ(ms1.size(), 3U);
  EXPECT_TRUE(ms1.contains(1));
  EXPECT_TRUE(ms1.contains(2));
  EXPECT_TRUE(ms1.contains(3));
  EXPECT_TRUE(ms2.empty());
}

TEST(MultisetTest, MergeEmptySet2) {
  multiset<int> ms1;
  multiset<int> ms2 = {1, 2, 3};
  ms1.merge(ms2);
  EXPECT_EQ(ms1.size(), 3U);
  EXPECT_TRUE(ms1.contains(1));
  EXPECT_TRUE(ms1.contains(2));
  EXPECT_TRUE(ms1.contains(3));
  EXPECT_TRUE(ms2.empty());
}

TEST(MultisetTest, MergeBothEmpty) {
  multiset<int> ms1, ms2;
  ms1.merge(ms2);
  EXPECT_TRUE(ms1.empty());
  EXPECT_TRUE(ms2.empty());
}

TEST(MultisetTest, MergeItself) {
  multiset<int> ms = {1, 2, 3};
  ms.merge(ms);
  EXPECT_EQ(ms.size(), 3U);
  EXPECT_TRUE(ms.contains(1));
  EXPECT_TRUE(ms.contains(2));
  EXPECT_TRUE(ms.contains(3));
}

TEST(MultisetTest, MergeNormal) {
  multiset<int> ms1 = {1, 2, 3};
  multiset<int> ms2 = {4, 5, 6};
  ms1.merge(ms2);
  EXPECT_EQ(ms1.size(), 6U);
  EXPECT_TRUE(ms1.contains(1));
  EXPECT_TRUE(ms1.contains(2));
  EXPECT_TRUE(ms1.contains(3));
  EXPECT_TRUE(ms1.contains(4));
  EXPECT_TRUE(ms1.contains(5));
  EXPECT_TRUE(ms1.contains(6));
  EXPECT_TRUE(ms2.empty());
}

TEST(MultisetTest, MergeWithDuplicates) {
  multiset<int> ms1 = {1, 2, 3, 4};
  multiset<int> ms2 = {4, 5, 6, 1};
  ms1.merge(ms2);
  EXPECT_EQ(ms1.size(), 8U);
  EXPECT_EQ(ms2.size(), 0U);
  EXPECT_EQ(ms1.count(1), 2U);
  EXPECT_EQ(ms1.count(2), 1U);
  EXPECT_EQ(ms1.count(3), 1U);
  EXPECT_EQ(ms1.count(4), 2U);
  EXPECT_EQ(ms1.count(5), 1U);
  EXPECT_EQ(ms1.count(6), 1U);
}

TEST(MultisetTest, BoundsUnexisted) {
  multiset<int> ms;
  EXPECT_EQ(ms.lower_bound(21), ms.end());
  EXPECT_EQ(ms.upper_bound(21), ms.end());
  EXPECT_EQ(ms.equal_range(21), (std::pair{ms.end(), ms.end()}));
}

TEST(MultisetTest, BoundsExisted) {
  multiset<int> ms = {1, 2, 3, 4, 5};
  EXPECT_EQ(ms.lower_bound(1), ms.begin());
  EXPECT_EQ(ms.upper_bound(1), ++ms.begin());
  EXPECT_EQ(ms.equal_range(1), (std::pair{ms.begin(), ++ms.begin()}));
}

TEST(MultisetTest, BoundsWithDuplicates) {
  multiset<int> ms = {1, 2, 3, 4, 5, 1, 1};
  EXPECT_EQ(ms.count(1), 3U);
}
}  // namespace s21