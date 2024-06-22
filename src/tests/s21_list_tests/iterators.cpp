#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(List_Iterators, begin) {
  s21::list<int> a = {1, 2, 3};
  EXPECT_EQ(*a.begin(), 1);
}

TEST(List_Iterators, end) {
  s21::list<int> a = {1, 2, 3};
  EXPECT_EQ(*(a.end() - 1), 3);
}