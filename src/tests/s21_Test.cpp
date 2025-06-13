//
// Created by rasko on 30.03.2025.
//
#include "s21_test.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout << "RUNNING TESTS ..." << std::endl;
  int ret{RUN_ALL_TESTS()};
  if (!ret)
    std::cout << "<<<SUCCESS>>>" << std::endl;
  else
    std::cout << "FAILED" << std::endl;
  return 0;
}
