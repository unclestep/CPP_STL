#include "s21_test.h"

namespace s21 {
    TEST(SetTest, DefaultConstructor) {
        set<int> s;
        EXPECT_TRUE(s.empty());
    }

    TEST(SetTest, InitializerListConstructor) {
        set<int> s = {1, 2, 3, 4};
        TEST_SET(s);

        EXPECT_EQ(s.size(), 4);
        EXPECT_TRUE(s.contains(1));
        EXPECT_TRUE(s.contains(2));
        EXPECT_TRUE(s.contains(3));
        EXPECT_TRUE(s.contains(4));
    }

    TEST(SetTest, RepeatedInitializerListConstructor) {
        set<int> s = {1, 1, 2, 2};
        TEST_SET(s);

        EXPECT_EQ(s.size(), 2);
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
        TEST_SET(s1);

        set<int> s2 = s1;
        TEST_SET(s2);

        EXPECT_EQ(s1.size(), s2.size());
        EXPECT_TRUE(std::equal(s1.begin(), s1.end(), s2.begin(), s2.end()));
        
    }

    TEST(SetTest, MoveConstructor) {
        set<int> s1 = {1, 2, 3, 4};
        TEST_SET(s1);

        set<int> s2 = std::move(s1);
        TEST_SET(s2);

        EXPECT_EQ(s1.size(), 0);
        EXPECT_EQ(s2.size(), 4);
        EXPECT_EQ(s1.begin(), s1.end());
        EXPECT_TRUE(s2.contains(1));
        EXPECT_TRUE(s2.contains(2));
        EXPECT_TRUE(s2.contains(3));
        EXPECT_TRUE(s2.contains(4));
    }

    TEST(SetTest, CopyAssignment) {
        set<int> s1 = {1, 2, 3, 4};
        TEST_SET(s1);

        set<int> s2;
        s2 = s1;
        TEST_SET(s2);

        EXPECT_EQ(s1.size(), s2.size());
        EXPECT_TRUE(std::equal(s1.begin(), s1.end(), s2.begin(), s2.end()));
        
        
    }

    TEST(SetTest, MoveAssignment) {
        set<int> s1 = {1, 2, 3, 4};
        TEST_SET(s1);
        
        set<int> s2;
        s2 = std::move(s1);
        TEST_SET(s2);

        EXPECT_EQ(s1.size(), 0);
        EXPECT_EQ(s2.size(), 4);
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
        EXPECT_EQ(s.size(), 0);
        EXPECT_EQ(s.begin(), s.end());
    }

    TEST(SetTest, ClearNonEmpty) {
        set<int> s = {1, 2, 3, 4, 5};
        s.clear();
        EXPECT_EQ(s.size(), 0);
        EXPECT_EQ(s.begin(), s.end());
    }

    TEST(SetTest, Insert1) {
        set<int> s;
        s.insert(1);
        TEST_SET(s);

        EXPECT_EQ(s.size(), 1);
        EXPECT_TRUE(s.contains(1));
    }

    TEST(SetTest, Insert2) {
        set<int> s = {1, 10, 20};
        s.insert(5);
        TEST_SET(s);

        EXPECT_EQ(s.size(), 4);
        EXPECT_TRUE(s.contains(5));
    }

    TEST(SetTest, Insert3) {
        set<int> s;
        for (int i = -10; i <= 10; ++i) {
            s.insert(i);
        }
        TEST_SET(s);
        EXPECT_EQ(s.size(), 21);

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
        TEST_SET(s);
        EXPECT_EQ(s.size(), 21);

        int exp = 10;
        for (auto it = --s.end();; --it, --exp) {
            EXPECT_EQ(*it, exp);
            if (it == begin()) break;
        }
    }
    
    TEST(SetTest, Insert5) {
        set<int> s;
        for (int i = 0; i <= 1000; ++i) {
            s.insert(i);
        }
        TEST_SET(s);
        EXPECT_EQ(s.size(), 1001);

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
        TEST_SET(s);
        EXPECT_EQ(s.size(), 21);

        int exp = 0;
        for (auto it = s.begin(); it != s.end(); ++it, ++exp) {
            EXPECT_EQ(*it, exp);
        }
    }

    TEST(SetTest, InsertAfterClear1) {
        set<int> s = {0, 21, 42};
        s.clear();
        s.insert(1);
        TEST_SET(s);
        EXPECT_EQ(s.size(), 1);
        EXPECT_TRUE(s.contains(1));
    }

    TEST(SetTest, InsertAfterClear2) {
        set<int> s = {0, 21, 42};
        s.clear();
        s.insert(21);
        TEST_SET(s);
        EXPECT_EQ(s.size(), 1);
        EXPECT_TRUE(s.contains(21));
    }

    TEST(SetTest, Erase1) {
        set<int> s = {1, 2, 3, 4, 5};
        auto it = s.find(1);
        s.erase(it);
        TEST_SET(s);
        EXPECT_EQ(s.size(), 4);
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
        TEST_SET(s);
        EXPECT_EQ(s.size(), 4);
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
        TEST_SET(s);
        EXPECT_EQ(s.size(), 4);
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
        TEST_SET(s);
        EXPECT_EQ(s.size(), 5);
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
        EXPECT_EQ(s.size(), 0);
        EXPECT_EQ(s.begin(), s.end());
    }

    TEST(SetTest, EraseEnd) {
        set<int> s;
        auto it = s.end();
        s.erase(it);
        EXPECT_EQ(s.size(), 0);
        EXPECT_EQ(s.begin(), s.end());
    }

    TEST(SetTest, EraseAll) {
        set<int> s;
        for (int i = 0; i <= 1000; ++i) {
            s.insert(i);
        }
        while (!s.empty()) {
            s.erase(s.begin());
            TEST_SET(s);
        }
        EXPECT_EQ(s.size(), 0);
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
            TEST_SET(s);
        }
        EXPECT_EQ(s.size(), 10);
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
        TEST_SET(s);
        EXPECT_EQ(s.size(), 0);
        EXPECT_EQ(s.begin(), s.end());
    }

    TEST(SetTest, EraseSameTwice) {
        set<int> s = {1, 2, 3, 4, 5};
        auto it = s.find(3);
        s.erase(it);
        TEST_SET(s);
        s.erase(it);
        TEST_SET(s);
        EXPECT_EQ(s.size(), 4);
        EXPECT_FALSE(s.contains(3));
        EXPECT_TRUE(s.contains(1));
        EXPECT_TRUE(s.contains(2));
        EXPECT_TRUE(s.contains(4));
        EXPECT_TRUE(s.contains(5));
    }

}