//
// Created by rasko on 30.03.2025.
//
#ifndef CPP2_S21_CONTAINERS_1_S21_TEST_H
#define CPP2_S21_CONTAINERS_1_S21_TEST_H
#include "../Containers/s21_containers.h"
#include "../Containers/s21_containersplus.h"
#include "gtest/gtest.h"

template <typename T>
bool RBTCheck(RBTNode<T>* node, RBTNode<T>* nil, int& blackHeight);

template <typename T>
void TEST_SET(const s21::set<T>& s);

#endif //CPP2_S21_CONTAINERS_1_S21_TEST_H
