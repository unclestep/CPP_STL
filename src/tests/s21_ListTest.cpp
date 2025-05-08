//
// Created by Valentine on 05.05.2025.
//
#include "s21_test.h"

namespace s21{
    TEST(ListTests, Test1){
        List<int> newList;

        newList.push_back(30);
        auto iterator = newList.begin();
        EXPECT_EQ(*iterator, 30);
        ++iterator;
        EXPECT_EQ(iterator, nullptr);
    }
    TEST(ListTests, Test2){
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
        for(auto it = newList.begin(); it != nullptr; ++it){
            EXPECT_EQ(*it, ch);
            ch -= 10;
        }
    }
    TEST(ListTests, Test3){
        List<int> newList;
        
        newList.push_back(30);
        newList.push_back(20);
        newList.push_back(10);
        newList.push_back(0);
        newList.push_front(40);
        int ch = 40;
        for(auto it = newList.begin(); it != nullptr; ++it){
            EXPECT_EQ(*it, ch);
            ch -= 10;
        }
    }
    TEST(ListTests, Test4){
        List<int> newList;

        newList.push_back(30);
        newList.push_back(20);
        newList.pop_back();
        auto it = newList.end();
        EXPECT_EQ(*it, 30);
    }
    TEST(ListTests, Test5){
        List<int> newList;
        newList.push_back(30);
        newList.push_back(20);
        newList.pop_back();
        
        auto it = newList.end();
        EXPECT_EQ(*it, 30);
    }
    TEST(ListTests, Test6){
        List<int> newList;
        newList.push_back(30);
        newList.push_back(40);
        newList.push_back(50);
        newList.push_back(60);        
        EXPECT_EQ(newList.size(), 4);
    }
    TEST(ListTests, Test7){
        List<int> newList;

        EXPECT_EQ(newList.size(), 0);
    }
    TEST(ListTests, Test8){
        List<int> newList;

        EXPECT_EQ(newList.empty(), true);
    }
    TEST(ListTests, Test9){
        List<int> newList;

        EXPECT_EQ(std::numeric_limits<std::size_t>::max()/sizeof(int), newList.max_size());
    }
    TEST(ListTests, Test10){
        List<int> newList {1, 2, 3, 4, 5};
        
        int checkList = 1;
        for(auto it = newList.begin(); it != nullptr; ++it){
            EXPECT_EQ(*it, checkList);
            ++checkList;           
        }
    }
    TEST(ListTests, Test11){
        List<int> newList {1, 2, 3, 5, 6, 7, 8};

        EXPECT_EQ(*(newList.insert(newList.begin(), 0)), 0);
    }
    TEST(ListTests, Test12){
        List<int> newList {1, 2, 3, 5, 6, 7, 8};
        
        EXPECT_EQ(*(newList.insert(newList.end(), 9)), 9);   
    }
    TEST(ListTests, Test13){
        List<int> newList {1, 2, 4, 5, 6, 7, 8};
        
        auto it = newList.begin();
        ++it;
        ++it;
        
        EXPECT_EQ(*(newList.insert(it, 3)), 3);

        int check = 1;
        
        for(auto it = newList.begin(); it != newList.end(); ++it){
            EXPECT_EQ(*it, check);
            check++;
        }        
    }
    TEST(ListTests, Test14){
        List<int> newList {1, 2, 4, 5, 6, 7, 8};
        
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
        List<int> newList {1, 2, 3, 4, 5, 6, 7, 8};
        
        List<int> copyList(newList);
        int counter = 1;
        for (auto it = copyList.begin(); it != copyList.end(); ++it) {
            EXPECT_EQ(*it, counter);
            counter++;
        }
    }
    TEST(ListTests, Test17) {
        List<int> newList {1, 2, 3, 4, 5, 6, 7, 8};
        
        List<int> movedList = std::move(newList);
        int counter = 1;
        for (auto it = movedList.begin(); it != movedList.end(); ++it) {
            EXPECT_EQ(*it, counter);
            counter++;
        }
        EXPECT_EQ(newList.begin(), nullptr);
    }
    TEST(ListTests, Test18) {
        List<int> newList {1, 2, 3, 4, 5, 6, 7, 8};
        
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
        List<int> newList {1, 2, 3, 4, 5, 6, 7, 8};
        
        EXPECT_EQ(newList.front(), 1);
        EXPECT_EQ(newList.back(), 8);
    }
    TEST(ListTests, Test20) {
        List<int> newList1 {1, 2, 3, 4, 5, 6, 7, 8};
        List<int> newList2 {10, 11, 12};
        
        newList1.swap(newList2);

        EXPECT_EQ(newList1.front(), 10);
        EXPECT_EQ(newList1.back(), 12);
        EXPECT_EQ(newList2.front(), 1);
        EXPECT_EQ(newList2.back(), 8);
    }
    TEST(ListTests, Test21) {
        List<int> newList1 {8, 7, 6, 5, 4, 3, 2, 1};

        newList1.sort();

        EXPECT_EQ(newList1.front(), 1);
        EXPECT_EQ(newList1.back(), 8);
        
    }
}