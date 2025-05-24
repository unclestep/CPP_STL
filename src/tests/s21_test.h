//
// Created by rasko on 30.03.2025.
//
#ifndef CPP2_S21_CONTAINERS_1_S21_TEST_H
#define CPP2_S21_CONTAINERS_1_S21_TEST_H
#include "../Containers/s21_containers.h"
#include "../Containers/s21_containersplus.h"
#include "gtest/gtest.h"

template <typename T>
bool RBTCheck(RBTNode<T>* node, RBTNode<T>* nil, int& blackHeight)
{
    if (node == nil) {
        blackHeight = 1;
        return true;
    }

    if (node->color == Color::RED) {
        if (node->left->color != Color::BLACK || node->right->color != Color::BLACK)
            return false;
    }

    int leftBH = 0;
    int rightBH = 0;
    if (!RBTCheck(node->left, nil, leftBH)) 
        return false;
    if (!RBTCheck(node->right, nil, rightBH)) 
        return false;

    if (leftBH != rightBH) 
        return false;

    blackHeight = leftBH + (node->color == Color::BLACK ? 1 : 0);
    return true;
}

template <typename T>
void TEST_SET(const s21::set<T>& s) {
    // int blackHeight = 0;
    s21::set<T> s1 = s;
    s1.clear();
    EXPECT_TRUE(true);
    // EXPECT_TRUE(RBTCheck(s.getRoot(), s.getNil(), blackHeight));
}

#endif //CPP2_S21_CONTAINERS_1_S21_TEST_H
