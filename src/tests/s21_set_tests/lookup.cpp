#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(Set_Lookup, find) {
  s21::set<int> a = {1, 2, 3};
  EXPECT_EQ(*a.find(3), 3);
}

TEST(Set_Lookup, contains_True) {
  s21::set<int> a = {1, 2, 3};
  EXPECT_EQ(a.contains(3), 1);
}

TEST(Set_Lookup, contains_False) {
  s21::set<int> a = {1, 2, 3};
  EXPECT_EQ(a.contains(4), 0);
}