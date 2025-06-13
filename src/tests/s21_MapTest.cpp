#include "s21_test.h"

namespace s21 {
TEST(MapTest, DefaultConstructor) {
  map<int, int> m;
  EXPECT_TRUE(m.empty());
}

TEST(MapTest, InitializerListConstructor) {
  map<int, std::string> m = {{1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}};

  EXPECT_EQ(m.size(), 4U);
  EXPECT_TRUE(m.contains(1));
  EXPECT_TRUE(m.contains(2));
  EXPECT_TRUE(m.contains(3));
  EXPECT_TRUE(m.contains(4));
}

TEST(MapTest, RepeatedInitializerListConstructor) {
  map<int, std::string> m = {{1, "one"}, {1, "one"}, {2, "two"}, {2, "two"}};

  EXPECT_EQ(m.size(), 2U);
  EXPECT_TRUE(m.contains(1));
  EXPECT_TRUE(m.contains(2));

  int one = 0, second = 0;
  for (auto it = m.begin(); it != m.end(); ++it) {
    if (it->second == "one") {
      ++one;
    } else if (it->second == "two") {
      ++second;
    }
  }

  EXPECT_EQ(one, 1);
  EXPECT_EQ(second, 1);
}

TEST(MapTest, CopyConstructor) {
  map<int, std::string> m1 = {
      {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}};

  map<int, std::string> m2 = m1;

  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_TRUE(std::equal(m1.begin(), m1.end(), m2.begin(), m2.end()));
}

TEST(MapTest, MoveConstructor) {
  map<int, std::string> m1 = {
      {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}};

  map<int, std::string> m2 = std::move(m1);

  EXPECT_EQ(m1.size(), 0U);
  EXPECT_EQ(m2.size(), 4U);
  EXPECT_EQ(m1.begin(), m1.end());
  EXPECT_TRUE(m2.contains(1));
  EXPECT_TRUE(m2.contains(2));
  EXPECT_TRUE(m2.contains(3));
  EXPECT_TRUE(m2.contains(4));
}

TEST(MapTest, CopyAssignment) {
  map<int, std::string> m1 = {
      {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}};

  map<int, std::string> m2;
  m2 = m1;

  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_TRUE(std::equal(m1.begin(), m1.end(), m2.begin(), m2.end()));
}

TEST(MapTest, MoveAssignment) {
  map<int, std::string> m1 = {
      {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}};

  map<int, std::string> m2;
  m2 = std::move(m1);

  EXPECT_EQ(m1.size(), 0U);
  EXPECT_EQ(m2.size(), 4U);
  EXPECT_EQ(m1.begin(), m1.end());
  EXPECT_TRUE(m2.contains(1));
  EXPECT_TRUE(m2.contains(2));
  EXPECT_TRUE(m2.contains(3));
  EXPECT_TRUE(m2.contains(4));
}

TEST(MapTest, MaxSize) {
  map<int, std::string> m = {{1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}};

  EXPECT_GT(m.max_size(), m.size());
}

TEST(MapTest, ClearEmpty) {
  map<int, std::string> m;
  m.clear();
  EXPECT_EQ(m.size(), 0U);
  EXPECT_EQ(m.begin(), m.end());
}

TEST(MapTest, ClearNonEmpty) {
  map<int, std::string> m = {{1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}};

  m.clear();
  EXPECT_EQ(m.size(), 0U);
  EXPECT_EQ(m.begin(), m.end());
}

TEST(MapTest, Insert1) {
  map<int, std::string> m;
  m.insert({1, "one"});

  EXPECT_EQ(m.size(), 1U);
  EXPECT_TRUE(m.contains(1));
}

TEST(MapTest, Insert2) {
  map<int, std::string> m = {{1, "one"}, {10, "ten"}, {20, "twenty"}};

  m.insert({5, "five"});

  EXPECT_EQ(m.size(), 4U);
  EXPECT_TRUE(m.contains(5));
}

TEST(MapTest, Insert3) {
  map<int, double> m;
  for (int i = -10; i <= 10; ++i) {
    m.insert({i, static_cast<double>(i)});
  }

  EXPECT_EQ(m.size(), 21U);

  double exp = -10.0;
  for (auto it = m.begin(); it != m.end(); ++it, ++exp) {
    EXPECT_EQ(it->first, static_cast<int>(exp));
    EXPECT_EQ(it->second, exp);
  }
}

TEST(MapTest, Insert4) {
  map<int, double> m;
  for (int i = 10; i >= -10; --i) {
    m.insert({i, static_cast<double>(i)});
  }

  EXPECT_EQ(m.size(), 21U);

  double exp = 10.0;
  for (auto it = --m.end();; --it, --exp) {
    EXPECT_EQ(it->first, static_cast<int>(exp));
    EXPECT_EQ(it->second, exp);
    if (it == m.begin()) break;
  }
}

TEST(MapTest, Insert5) {
  map<int, double> m;
  for (int i = 0; i <= 1000; ++i) {
    m.insert({i, static_cast<double>(i)});
  }

  EXPECT_EQ(m.size(), 1001U);

  double exp = 0.0;
  for (auto it = m.begin(); it != m.end(); ++it, ++exp) {
    EXPECT_EQ(it->first, static_cast<int>(exp));
    EXPECT_EQ(it->second, exp);
  }
}

TEST(MapTest, InsertDuplicates) {
  map<int, double> m;
  for (int i = 0; i <= 1000; ++i) {
    auto res = m.insert({i % 21, static_cast<double>(i % 21)});
    bool isDuplicate = (i / 21) >= 1;
    EXPECT_EQ(res.second, !isDuplicate);
  }

  EXPECT_EQ(m.size(), 21U);

  double exp = 0.0;
  for (auto it = m.begin(); it != m.end(); ++it, ++exp) {
    EXPECT_EQ(it->first, static_cast<int>(exp));
    EXPECT_EQ(it->second, exp);
  }
}

TEST(MapTest, InsertAfterClear1) {
  map<int, std::string> m = {
      {0, "zero"}, {21, "twenty one"}, {42, "fourty two"}};
  m.clear();

  m.insert({1, "one"});

  EXPECT_EQ(m.size(), 1U);
  EXPECT_TRUE(m.contains(1));
}

TEST(MapTest, InsertAfterClear2) {
  map<int, std::string> m = {
      {0, "zero"}, {21, "twenty one"}, {42, "fourty two"}};
  m.clear();

  m.insert({21, "twenty one"});

  EXPECT_EQ(m.size(), 1U);
  EXPECT_TRUE(m.contains(21));
}

TEST(MapTest, InsertKeyValueSeparately) {
  map<int, std::string> m = {
      {0, "zero"}, {21, "twenty one"}, {42, "fourty two"}};

  m.insert(65, "sixty five");

  EXPECT_EQ(m.size(), 4U);
  EXPECT_TRUE(m.contains(65));
}

TEST(MapTest, InsertOrAssign1) {
  map<int, std::string> m = {
      {0, "zero"}, {21, "twenty one"}, {42, "fourty two"}};

  m.insert_or_assign(65, "sixty five");

  EXPECT_EQ(m.size(), 4U);
  EXPECT_TRUE(m.contains(65));
}

TEST(MapTest, InsertOrAssign2) {
  map<int, std::string> m = {
      {0, "zero"}, {21, "twenty one"}, {42, "fourty two"}};

  m.insert_or_assign(21, "not twenty one");

  EXPECT_EQ(m.size(), 3U);
  EXPECT_TRUE(m.contains(21));
  EXPECT_EQ(m[21], "not twenty one");
}

TEST(MapTest, Erase1) {
  map<int, std::string> m = {
      {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}};

  auto it = m.find(1);
  m.erase(it);

  EXPECT_EQ(m.size(), 4U);
  EXPECT_FALSE(m.contains(1));
  EXPECT_TRUE(m.contains(2));
  EXPECT_TRUE(m.contains(3));
  EXPECT_TRUE(m.contains(4));
  EXPECT_TRUE(m.contains(5));
}

TEST(MapTest, Erase2) {
  map<int, std::string> m = {
      {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}};

  auto it = m.find(5);
  m.erase(it);

  EXPECT_EQ(m.size(), 4U);
  EXPECT_FALSE(m.contains(5));
  EXPECT_TRUE(m.contains(4));
  EXPECT_TRUE(m.contains(3));
  EXPECT_TRUE(m.contains(2));
  EXPECT_TRUE(m.contains(1));
}

TEST(MapTest, Erase3) {
  map<int, std::string> m = {
      {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}};

  auto it = m.find(3);
  m.erase(it);

  EXPECT_EQ(m.size(), 4U);
  EXPECT_FALSE(m.contains(3));
  EXPECT_TRUE(m.contains(1));
  EXPECT_TRUE(m.contains(2));
  EXPECT_TRUE(m.contains(4));
  EXPECT_TRUE(m.contains(5));
}

TEST(MapTest, EraseUnexisted) {
  map<int, std::string> m = {
      {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}};

  auto it = m.find(6);
  m.erase(it);

  EXPECT_EQ(m.size(), 5U);
  for (size_t i = 1; i <= 5; ++i) {
    EXPECT_TRUE(m.contains(i));
  }
}

TEST(MapTest, EraseBegin) {
  map<int, std::string> m;
  auto it = m.begin();
  m.erase(it);
  EXPECT_EQ(m.size(), 0U);
  EXPECT_EQ(m.begin(), m.end());
}

TEST(MapTest, EraseEnd) {
  map<int, std::string> m;
  auto it = m.end();
  m.erase(it);
  EXPECT_EQ(m.size(), 0U);
  EXPECT_EQ(m.begin(), m.end());
}

TEST(MapTest, EraseAll) {
  map<int, int> m;
  for (int i = 0; i <= 1000; ++i) {
    m.insert({i, i});
  }
  while (!m.empty()) {
    m.erase(m.begin());
  }
  EXPECT_EQ(m.size(), 0U);
  EXPECT_EQ(m.begin(), m.end());
}

TEST(MapTest, EraseOdd) {
  map<int, double> m;
  for (int i = 1; i <= 21; ++i) {
    m.insert({i, static_cast<double>(i)});
  }
  for (int j = 1; j <= 21; j += 2) {
    auto it = m.find(j);
    m.erase(it);
  }
  EXPECT_EQ(m.size(), 10U);
  for (int z = 2; z <= 20; z += 2) {
    EXPECT_TRUE(m.contains(z));
  }
  for (int w = 1; w <= 21; w += 2) {
    EXPECT_FALSE(m.contains(w));
  }
}

TEST(MapTest, EraseSingle) {
  map<int, std::string> m = {{21, "twenty one"}};
  auto it = m.begin();
  m.erase(it);
  EXPECT_EQ(m.size(), 0U);
  EXPECT_EQ(m.begin(), m.end());
}

TEST(MapTest, InsertManyEmptySet) {
  map<int, std::string> m;
  auto results = m.insert_many(std::pair{1, "one"}, std::pair{2, "two"},
                               std::pair{3, "three"}, std::pair{4, "four"},
                               std::pair{5, "five"});
  EXPECT_EQ(m.size(), 5U);
  for (size_t i = 1; i <= 5; ++i) {
    EXPECT_TRUE(m.contains(i));
  }
  for (const auto &pair : results) {
    EXPECT_TRUE(pair.second);
  }
}

TEST(MapTest, InsertManyNonEmptySet) {
  map<int, std::string> m = {{0, "zero"}};
  auto results = m.insert_many(std::pair{1, "one"}, std::pair{2, "two"},
                               std::pair{3, "three"}, std::pair{4, "four"},
                               std::pair{5, "five"});
  EXPECT_EQ(m.size(), 6U);
  for (size_t i = 0; i <= 5; ++i) {
    EXPECT_TRUE(m.contains(i));
  }
  for (const auto &pair : results) {
    EXPECT_TRUE(pair.second);
  }
}

TEST(MapTest, InsertManyWithDuplicates) {
  map<int, std::string> m;
  auto results = m.insert_many(std::pair{1, "one"}, std::pair{2, "two"},
                               std::pair{1, "one"}, std::pair{2, "two"},
                               std::pair{5, "five"});

  EXPECT_EQ(m.size(), 3U);

  EXPECT_TRUE(m.contains(1));
  EXPECT_TRUE(m.contains(2));
  EXPECT_FALSE(m.contains(3));
  EXPECT_FALSE(m.contains(4));
  EXPECT_TRUE(m.contains(5));

  EXPECT_TRUE(results[0].second);
  EXPECT_TRUE(results[1].second);
  EXPECT_FALSE(results[2].second);
  EXPECT_FALSE(results[3].second);
  EXPECT_TRUE(results[4].second);
}

TEST(MapTest, InsertManyInDuplicates1) {
  map<int, std::string> m = {std::pair{1, "one"}, std::pair{2, "two"},
                             std::pair{1, "one"}, std::pair{2, "two"},
                             std::pair{5, "five"}};
  auto results = m.insert_many(std::pair{1, "one"}, std::pair{2, "two"},
                               std::pair{1, "one"}, std::pair{2, "two"},
                               std::pair{5, "five"});

  EXPECT_EQ(m.size(), 3U);

  EXPECT_TRUE(m.contains(1));
  EXPECT_TRUE(m.contains(2));
  EXPECT_FALSE(m.contains(3));
  EXPECT_FALSE(m.contains(4));
  EXPECT_TRUE(m.contains(5));

  for (const auto &pair : results) {
    EXPECT_FALSE(pair.second);
  }
}

TEST(MapTest, InsertManyInDuplicates2) {
  map<int, std::string> m = {std::pair{1, "one"}, std::pair{2, "two"},
                             std::pair{1, "one"}, std::pair{2, "two"},
                             std::pair{5, "five"}};
  auto results = m.insert_many(std::pair{1, "one"}, std::pair{2, "two"},
                               std::pair{1, "one"}, std::pair{2, "two"},
                               std::pair{5, "five"}, std::pair{6, "six"});

  EXPECT_EQ(m.size(), 4U);

  EXPECT_TRUE(m.contains(1));
  EXPECT_TRUE(m.contains(2));
  EXPECT_FALSE(m.contains(3));
  EXPECT_FALSE(m.contains(4));
  EXPECT_TRUE(m.contains(5));
  EXPECT_TRUE(m.contains(6));

  for (size_t i = 0; i < 5; ++i) {
    EXPECT_FALSE(results[i].second);
  }
  EXPECT_TRUE(results[5].second);
}

TEST(MapTest, InsertManyNothing1) {
  map<int, std::string> m = {{21, "twenty one"}};
  auto results = m.insert_many();
  EXPECT_EQ(m.size(), 1U);
  EXPECT_TRUE(m.contains(21));
  EXPECT_TRUE(results.empty());
}

TEST(MapTest, InsertManyNothing2) {
  map<int, std::string> m;
  auto results = m.insert_many();
  EXPECT_TRUE(m.empty());
  EXPECT_TRUE(results.empty());
}

TEST(MapTest, MergeEmptySet1) {
  map<int, std::string> m1 = {{1, "one"}, {2, "two"}, {3, "three"}};
  map<int, std::string> m2;

  m1.merge(m2);

  EXPECT_EQ(m1.size(), 3U);
  EXPECT_TRUE(m1.contains(1));
  EXPECT_TRUE(m1.contains(2));
  EXPECT_TRUE(m1.contains(3));
  EXPECT_TRUE(m2.empty());
}

TEST(MapTest, MergeEmptySet2) {
  map<int, std::string> m1;
  map<int, std::string> m2 = {{1, "one"}, {2, "two"}, {3, "three"}};

  m1.merge(m2);

  EXPECT_EQ(m1.size(), 3U);
  EXPECT_TRUE(m1.contains(1));
  EXPECT_TRUE(m1.contains(2));
  EXPECT_TRUE(m1.contains(3));
  EXPECT_TRUE(m2.empty());
}

TEST(MapTest, MergeBothEmpty) {
  map<int, std::string> m1, m2;
  m1.merge(m2);

  EXPECT_TRUE(m1.empty());
  EXPECT_TRUE(m2.empty());
}

TEST(MapTest, MergeItself) {
  map<int, std::string> m = {{1, "one"}, {2, "two"}, {3, "three"}};

  m.merge(m);

  EXPECT_EQ(m.size(), 3U);
  EXPECT_TRUE(m.contains(1));
  EXPECT_TRUE(m.contains(2));
  EXPECT_TRUE(m.contains(3));
}

TEST(MapTest, MergeNormal) {
  map<int, std::string> m1 = {{1, "one"}, {2, "two"}, {3, "three"}};
  map<int, std::string> m2 = {{4, "four"}, {5, "five"}, {6, "six"}};

  m1.merge(m2);

  EXPECT_EQ(m1.size(), 6U);
  for (size_t i = 1; i <= 6; ++i) {
    EXPECT_TRUE(m1.contains(i));
  }
  for (size_t j = 4; j <= 6; ++j) {
    EXPECT_FALSE(m2.contains(j));
  }
  EXPECT_TRUE(m2.empty());
}

TEST(MapTest, MergeWithDuplicates) {
  map<int, std::string> m1 = {
      {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}};
  map<int, std::string> m2 = {{4, "four"}, {5, "five"}, {6, "six"}, {1, "one"}};

  m1.merge(m2);

  EXPECT_EQ(m1.size(), 6U);
  for (size_t i = 1; i <= 6; ++i) {
    EXPECT_TRUE(m1.contains(i));
  }
  EXPECT_TRUE(m2.contains(4));
  EXPECT_FALSE(m2.contains(5));
  EXPECT_FALSE(m2.contains(6));
  EXPECT_TRUE(m2.contains(1));
  EXPECT_EQ(m2.size(), 2U);
}

TEST(MapTest, SquareBracketsOperator) {
  map<int, std::string> m;
  m[21] = "twenty one";
  EXPECT_EQ(m[21], "twenty one");
  EXPECT_EQ(m.size(), 1U);
  m[21] = "i was here once";
  EXPECT_EQ(m[21], "i was here once");
  EXPECT_EQ(m.size(), 1U);
}

TEST(MapTest, AtOperator1) {
  map<int, std::string> m;
  EXPECT_THROW({ m.at(21); }, std::out_of_range);
}

TEST(MapTest, AtOperator2) {
  map<int, std::string> m;
  m[21] = "twenty one";
  EXPECT_EQ(m.at(21), "twenty one");
}
}  // namespace s21