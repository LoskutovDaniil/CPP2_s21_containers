#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(Multiset_Iterators, begin) {
  s21::multiset<int> a = {1, 2};
  EXPECT_EQ(*a.begin(), 1);
}

TEST(Multiset_Iterators, end) {
  s21::multiset<int> a = {1, 2};
  EXPECT_EQ(*(a.end() - 1), 2);
}