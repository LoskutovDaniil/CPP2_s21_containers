#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(Vector_Iterators, begin) {
  s21::vector<int> a = {1, 2, 3};
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(*a.begin(), 1);
}

TEST(Vector_Iterators, end) {
  s21::vector<int> a = {1, 2, 3};
  EXPECT_EQ(*(a.end() - 1), 3);
}