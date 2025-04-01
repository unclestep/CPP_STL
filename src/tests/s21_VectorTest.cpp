//
// Created by rasko on 31.03.2025.
//
#include "s21_test.h"

TEST(VectorTests, Test1){
    Vector<int> v = {1, 2, 3, 4, 5};
    int counter = 1;
    for(Vector<int>::iterator it = v.begin();  it != v.end(); it++){
        EXPECT_EQ(counter, *it);
        counter++;
    }
}

TEST(VectorTests, Test2){
    Vector<double> v = {1.0, 2.0, 3.0, 4.0, 5.0};
    int counter = 1.0;
    for(Vector<double>::iterator it = v.begin();  it != v.end(); it++){
    EXPECT_EQ(counter, *it);
    counter++;
    }
}

TEST(VectorTests, Test3){
    Vector<double> v = {1.0, 2.0, 3.0, 4.0, 5.0};
    int counter = 1.0;
    v.push_back(6.0);
    for(Vector<double>::iterator it = v.begin();  it != v.end(); it++){
        EXPECT_EQ(counter, *it);
        counter++;
    }
}

TEST(VectorTests, Test4){
    Vector<double> v = {1.0, 2.0, 3.0, 4.0, 5.0};
    v.push_back(6.0);
    v.at(2);
	EXPECT_EQ(v.at(2), 3.0);
}

TEST(VectorTests, Test5){
	Vector<int> v = {1, 2, 3, 4, 5};
	v.push_back(6);
	Vector<int> v1;
	v1 = std::move(v);
	v1.at(2);
	EXPECT_EQ(v1.at(2), 3);
}

TEST(VectorTests, Test6){
	Vector<int> v = {1, 2, 3, 4, 5};
	v.push_back(6);
	EXPECT_EQ(v[0], 1);
}
TEST(VectorTests, Test7){
	Vector<int> v = {1, 2, 3, 4, 5};
	v.push_back(6);
	v.push_back(7);
	EXPECT_EQ(v.front(), 1);
}
TEST(VectorTests, Test8){
	Vector<int> v = {1, 2, 3, 4, 5};
	v.push_back(6);
	EXPECT_EQ(v.back(), 6);
}
TEST(VectorTests, Test9){
	Vector<int> v = {1, 2, 3, 4, 5};
	v.push_back(6);
	EXPECT_EQ(*v.data(), 1);
}
TEST(VectorTests, Test10){
	Vector<int> v = {1, 2, 3, 4, 5};
	v.push_back(6);
	EXPECT_EQ(v.empty(), false);
}
TEST(VectorTests, Test11){
	Vector<int> v = {};
	EXPECT_EQ(v.empty(), true);
}
TEST(VectorTests, Test12){
	Vector<int> v = {1};
	EXPECT_EQ(v.empty(), false);
}

TEST(VectorTests, Test13){
	Vector<int> v = {1};
	std::vector<int> vorg;
	EXPECT_EQ(vorg.max_size(), v.max_size());
}

TEST(VectorTests, Test14){
	Vector<double> v = {1};
	std::vector<double> vorg;
	EXPECT_EQ(vorg.max_size(), v.max_size());
}

TEST(VectorTests, Test15){
	Vector<int> v = {1};
	EXPECT_EQ(*v.data(), v[0]);
}
TEST(VectorTests, Test16){
	Vector<char> v = {'a'};
	std::vector<char> vorg;
	EXPECT_EQ(vorg.max_size(), v.max_size());
}
TEST(VectorTests, Test17){
	Vector<int> v {5, 12, 13, 14};
	std::vector<int> vorg {1, 2, 3, 4};
	EXPECT_EQ(vorg.capacity(), v.capacity());
}
