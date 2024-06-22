#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(Set_Iterators, begin) {
  s21::set<int> a = {1, 2, 3};
  EXPECT_EQ(*a.begin(), 1);
}

TEST(Set_Iterators, end) {
  s21::set<int> a = {1, 2, 3};
  EXPECT_EQ(*(a.end() - 1), 3);
}