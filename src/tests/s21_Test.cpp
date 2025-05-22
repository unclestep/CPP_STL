//
// Created by rasko on 30.03.2025.
//
#include "s21_test.h"

template <typename T>
bool RBTCheck(RBTNode<T>* node, RBTNode<T>* nil, int& blackHeight) {
    int leftBlackHeight = 0, rightBlackHeight = 0;
    int flag = 1;

    if (node == nil) {
        blackHeight = 0;
    } else {
        if (node->parent == nil && node->color != Color::BLACK) {
            flag = 0;
        }
        if (flag && node->color == Color::RED &&
            (node->left->color != Color::BLACK || node->right->color != Color::BLACK)) {
            flag = 0;
        }
        if (flag && !RBTCheck(node->left, nil, leftBlackHeight)) {
            flag = 0;
        }
        if (flag && !RBTCheck(node->right, nil, rightBlackHeight)) {
            flag = 0;
        }
        if (flag && leftBlackHeight != rightBlackHeight) {
            flag = 0;
        }
        if (flag) {
            blackHeight = leftBlackHeight + (node->color == Color::BLACK);
        }
    }
    return flag;
}

template <typename T>
void TEST_SET(const s21::set<T>& s) {
    int blackHeight = 0;
    EXPECT_TRUE(RBTCheck(s.getRoot(), s.getNil(), blackHeight));
}

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    std::cout << "RUNNING TESTS ..." << std::endl;
    int ret{RUN_ALL_TESTS()};
    if (!ret)
        std::cout << "<<<SUCCESS>>>" << std::endl;
    else
        std::cout << "FAILED" << std::endl;
    return 0;
}
