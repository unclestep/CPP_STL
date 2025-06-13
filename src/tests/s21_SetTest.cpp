#include "s21_test.h"

namespace s21 {
TEST(SetTest, DefaultConstructor) {
  set<int> s;
  EXPECT_TRUE(s.empty());
}

TEST(SetTest, InitializerListConstructor) {
  set<int> s = {1, 2, 3, 4};

  EXPECT_EQ(s.size(), 4U);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
  EXPECT_TRUE(s.contains(4));
}

TEST(SetTest, RepeatedInitializerListConstructor) {
  set<int> s = {1, 1, 2, 2};

  EXPECT_EQ(s.size(), 2U);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));

  int one = 0, second = 0;
  for (auto it = s.begin(); it != s.end(); ++it) {
    if (*it == 1) {
      ++one;
    } else if (*it == 2) {
      ++second;
    }
  }
  EXPECT_EQ(one, 1);
  EXPECT_EQ(second, 1);
}

TEST(SetTest, CopyConstructor) {
  set<int> s1 = {1, 2, 3, 4};

  set<int> s2 = s1;

  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_TRUE(std::equal(s1.begin(), s1.end(), s2.begin(), s2.end()));
}

TEST(SetTest, MoveConstructor) {
  set<int> s1 = {1, 2, 3, 4};

  set<int> s2 = std::move(s1);

  EXPECT_EQ(s1.size(), 0U);
  EXPECT_EQ(s2.size(), 4U);
  EXPECT_EQ(s1.begin(), s1.end());
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
  EXPECT_TRUE(s2.contains(4));
}

TEST(SetTest, CopyAssignment) {
  set<int> s1 = {1, 2, 3, 4};

  set<int> s2;
  s2 = s1;

  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_TRUE(std::equal(s1.begin(), s1.end(), s2.begin(), s2.end()));
}

TEST(SetTest, MoveAssignment) {
  set<int> s1 = {1, 2, 3, 4};

  set<int> s2;
  s2 = std::move(s1);

  EXPECT_EQ(s1.size(), 0U);
  EXPECT_EQ(s2.size(), 4U);
  EXPECT_EQ(s1.begin(), s1.end());
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
  EXPECT_TRUE(s2.contains(4));
}

TEST(SetTest, MaxSize) {
  set<int> s = {1, 2, 3, 4};
  EXPECT_GT(s.max_size(), s.size());
}

TEST(SetTest, ClearEmpty) {
  set<int> s;
  s.clear();
  EXPECT_EQ(s.size(), 0U);
  EXPECT_EQ(s.begin(), s.end());
}

TEST(SetTest, ClearNonEmpty) {
  set<int> s = {1, 2, 3, 4, 5};
  s.clear();
  EXPECT_EQ(s.size(), 0U);
  EXPECT_EQ(s.begin(), s.end());
}

TEST(SetTest, Insert1) {
  set<int> s;
  s.insert(1);

  EXPECT_EQ(s.size(), 1U);
  EXPECT_TRUE(s.contains(1));
}

TEST(SetTest, Insert2) {
  set<int> s = {1, 10, 20};
  s.insert(5);

  EXPECT_EQ(s.size(), 4U);
  EXPECT_TRUE(s.contains(5));
}

TEST(SetTest, Insert3) {
  set<int> s;
  for (int i = -10; i <= 10; ++i) {
    s.insert(i);
  }
  EXPECT_EQ(s.size(), 21U);

  int exp = -10;
  for (auto it = s.begin(); it != s.end(); ++it, ++exp) {
    EXPECT_EQ(*it, exp);
  }
}

TEST(SetTest, Insert4) {
  set<int> s;
  for (int i = 10; i >= -10; --i) {
    s.insert(i);
  }
  EXPECT_EQ(s.size(), 21U);

  int exp = 10;
  for (auto it = --s.end();; --it, --exp) {
    EXPECT_EQ(*it, exp);
    if (it == s.begin()) break;
  }
}

TEST(SetTest, Insert5) {
  set<int> s;
  for (int i = 0; i <= 1000; ++i) {
    s.insert(i);
  }
  EXPECT_EQ(s.size(), 1001U);

  int exp = 0;
  for (auto it = s.begin(); it != s.end(); ++it, ++exp) {
    EXPECT_EQ(*it, exp);
  }
}

TEST(SetTest, InsertDuplicates) {
  set<int> s;
  for (int i = 0; i <= 1000; ++i) {
    auto res = s.insert(i % 21);
    bool isDuplicate = (i / 21) >= 1;
    EXPECT_EQ(res.second, !isDuplicate);
  }
  EXPECT_EQ(s.size(), 21U);

  int exp = 0;
  for (auto it = s.begin(); it != s.end(); ++it, ++exp) {
    EXPECT_EQ(*it, exp);
  }
}

TEST(SetTest, InsertAfterClear1) {
  set<int> s = {0, 21, 42};
  s.clear();
  s.insert(1);
  EXPECT_EQ(s.size(), 1U);
  EXPECT_TRUE(s.contains(1));
}

TEST(SetTest, InsertAfterClear2) {
  set<int> s = {0, 21, 42};
  s.clear();
  s.insert(21);
  EXPECT_EQ(s.size(), 1U);
  EXPECT_TRUE(s.contains(21));
}

TEST(SetTest, Erase1) {
  set<int> s = {1, 2, 3, 4, 5};
  auto it = s.find(1);
  s.erase(it);
  EXPECT_EQ(s.size(), 4U);
  EXPECT_FALSE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
  EXPECT_TRUE(s.contains(4));
  EXPECT_TRUE(s.contains(5));
}

TEST(SetTest, Erase2) {
  set<int> s = {1, 2, 3, 4, 5};
  auto it = s.find(5);
  s.erase(it);
  EXPECT_EQ(s.size(), 4U);
  EXPECT_FALSE(s.contains(5));
  EXPECT_TRUE(s.contains(4));
  EXPECT_TRUE(s.contains(3));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(1));
}

TEST(SetTest, Erase3) {
  set<int> s = {1, 2, 3, 4, 5};
  auto it = s.find(3);
  s.erase(it);
  EXPECT_EQ(s.size(), 4U);
  EXPECT_FALSE(s.contains(3));
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(4));
  EXPECT_TRUE(s.contains(5));
}

TEST(SetTest, EraseUnexisted) {
  set<int> s = {1, 2, 3, 4, 5};
  auto it = s.find(6);
  s.erase(it);
  EXPECT_EQ(s.size(), 5U);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
  EXPECT_TRUE(s.contains(4));
  EXPECT_TRUE(s.contains(5));
}

TEST(SetTest, EraseBegin) {
  set<int> s;
  auto it = s.begin();
  s.erase(it);
  EXPECT_EQ(s.size(), 0U);
  EXPECT_EQ(s.begin(), s.end());
}

TEST(SetTest, EraseEnd) {
  set<int> s;
  auto it = s.end();
  s.erase(it);
  EXPECT_EQ(s.size(), 0U);
  EXPECT_EQ(s.begin(), s.end());
}

TEST(SetTest, EraseAll) {
  set<int> s;
  for (int i = 0; i <= 1000; ++i) {
    s.insert(i);
  }
  while (!s.empty()) {
    s.erase(s.begin());
  }
  EXPECT_EQ(s.size(), 0U);
  EXPECT_EQ(s.begin(), s.end());
}

TEST(SetTest, EraseOdd) {
  set<int> s;
  for (int i = 1; i <= 21; ++i) {
    s.insert(i);
  }
  for (int j = 1; j <= 21; j += 2) {
    auto it = s.find(j);
    s.erase(it);
  }
  EXPECT_EQ(s.size(), 10U);
  for (int z = 2; z <= 20; z += 2) {
    EXPECT_TRUE(s.contains(z));
  }
  for (int w = 1; w <= 21; w += 2) {
    EXPECT_FALSE(s.contains(w));
  }
}

TEST(SetTest, EraseSingle) {
  set<int> s = {21};
  auto it = s.begin();
  s.erase(it);
  EXPECT_EQ(s.size(), 0U);
  EXPECT_EQ(s.begin(), s.end());
}

TEST(SetTest, InsertManyEmptySet) {
  set<int> s;
  auto results = s.insert_many(1, 2, 3, 4, 5);
  EXPECT_EQ(s.size(), 5U);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
  EXPECT_TRUE(s.contains(4));
  EXPECT_TRUE(s.contains(5));
  for (const auto &pair : results) {
    EXPECT_TRUE(pair.second);
  }
}

TEST(SetTest, InsertManyNonEmptySet) {
  set<int> s = {0};
  auto results = s.insert_many(1, 2, 3, 4, 5);
  EXPECT_EQ(s.size(), 6U);
  EXPECT_TRUE(s.contains(0));
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
  EXPECT_TRUE(s.contains(4));
  EXPECT_TRUE(s.contains(5));
  for (const auto &pair : results) {
    EXPECT_TRUE(pair.second);
  }
}

TEST(SetTest, InsertManyWithDuplicates) {
  set<int> s;
  auto results = s.insert_many(1, 2, 1, 2, 5);

  EXPECT_EQ(s.size(), 3U);

  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_FALSE(s.contains(3));
  EXPECT_FALSE(s.contains(4));
  EXPECT_TRUE(s.contains(5));

  EXPECT_TRUE(results[0].second);
  EXPECT_TRUE(results[1].second);
  EXPECT_FALSE(results[2].second);
  EXPECT_FALSE(results[3].second);
  EXPECT_TRUE(results[4].second);
}

TEST(SetTest, InsertManyInDuplicates1) {
  set<int> s = {1, 2, 1, 2, 5};
  auto results = s.insert_many(1, 2, 1, 2, 5);

  EXPECT_EQ(s.size(), 3U);

  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_FALSE(s.contains(3));
  EXPECT_FALSE(s.contains(4));
  EXPECT_TRUE(s.contains(5));

  for (const auto &pair : results) {
    EXPECT_FALSE(pair.second);
  }
}

TEST(SetTest, InsertManyInDuplicates2) {
  set<int> s = {1, 2, 1, 2, 5};
  auto results = s.insert_many(1, 2, 1, 2, 5, 6);

  EXPECT_EQ(s.size(), 4U);

  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_FALSE(s.contains(3));
  EXPECT_FALSE(s.contains(4));
  EXPECT_TRUE(s.contains(5));
  EXPECT_TRUE(s.contains(6));

  EXPECT_FALSE(results[0].second);
  EXPECT_FALSE(results[1].second);
  EXPECT_FALSE(results[2].second);
  EXPECT_FALSE(results[3].second);
  EXPECT_FALSE(results[4].second);
  EXPECT_TRUE(results[5].second);
}

TEST(SetTest, InsertManyNothing1) {
  set<int> s = {21};
  auto results = s.insert_many();
  EXPECT_EQ(s.size(), 1U);
  EXPECT_TRUE(s.contains(21));
  EXPECT_TRUE(results.empty());
}

TEST(SetTest, InsertManyNothing2) {
  set<int> s;
  auto results = s.insert_many();
  EXPECT_TRUE(s.empty());
  EXPECT_TRUE(results.empty());
}

TEST(SetTest, MergeEmptySet1) {
  set<int> s1 = {1, 2, 3};
  set<int> s2;
  s1.merge(s2);
  EXPECT_EQ(s1.size(), 3U);
  EXPECT_TRUE(s1.contains(1));
  EXPECT_TRUE(s1.contains(2));
  EXPECT_TRUE(s1.contains(3));
  EXPECT_TRUE(s2.empty());
}

TEST(SetTest, MergeEmptySet2) {
  set<int> s1;
  set<int> s2 = {1, 2, 3};
  s1.merge(s2);
  EXPECT_EQ(s1.size(), 3U);
  EXPECT_TRUE(s1.contains(1));
  EXPECT_TRUE(s1.contains(2));
  EXPECT_TRUE(s1.contains(3));
  EXPECT_TRUE(s2.empty());
}

TEST(SetTest, MergeBothEmpty) {
  set<int> s1, s2;
  s1.merge(s2);
  EXPECT_TRUE(s1.empty());
  EXPECT_TRUE(s2.empty());
}

TEST(SetTest, MergeItself) {
  set<int> s = {1, 2, 3};
  s.merge(s);
  EXPECT_EQ(s.size(), 3U);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
}

TEST(SetTest, MergeNormal) {
  set<int> s1 = {1, 2, 3};
  set<int> s2 = {4, 5, 6};
  s1.merge(s2);
  EXPECT_EQ(s1.size(), 6U);
  EXPECT_TRUE(s1.contains(1));
  EXPECT_TRUE(s1.contains(2));
  EXPECT_TRUE(s1.contains(3));
  EXPECT_TRUE(s1.contains(4));
  EXPECT_TRUE(s1.contains(5));
  EXPECT_TRUE(s1.contains(6));
  EXPECT_TRUE(s2.empty());
}

TEST(SetTest, MergeWithDuplicates) {
  set<int> s1 = {1, 2, 3, 4};
  set<int> s2 = {4, 5, 6, 1};
  s1.merge(s2);
  EXPECT_EQ(s1.size(), 6U);
  EXPECT_TRUE(s1.contains(1));
  EXPECT_TRUE(s1.contains(2));
  EXPECT_TRUE(s1.contains(3));
  EXPECT_TRUE(s1.contains(4));
  EXPECT_TRUE(s1.contains(5));
  EXPECT_TRUE(s1.contains(6));
  EXPECT_EQ(s2.size(), 2U);
}

}  // namespace s21