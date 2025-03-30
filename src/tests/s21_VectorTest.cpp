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