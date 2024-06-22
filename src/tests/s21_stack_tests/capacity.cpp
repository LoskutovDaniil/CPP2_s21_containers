#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(Stack_Capacity, empty_True) {
  s21::stack<int> a = {};
  EXPECT_EQ(a.empty(), 1);
}

TEST(Stack_Capacity, empty_False) {
  s21::stack<int> a = {0};
  EXPECT_EQ(a.empty(), 0);
}

TEST(Stack_Capacity, size) {
  s21::stack<int> a = {1, 2, 3, 4, 5};
  EXPECT_EQ(a.size(), 5);
}