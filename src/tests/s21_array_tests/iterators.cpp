#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(Array_Iterators, begin) {
  s21::array<int, 2> a = {1, 2};

  EXPECT_EQ(*a.begin(), 1);
}

TEST(Array_Iterators, end) {
  s21::array<int, 2> a = {1, 2};

  EXPECT_EQ(*(a.end() - 1), 2);
}