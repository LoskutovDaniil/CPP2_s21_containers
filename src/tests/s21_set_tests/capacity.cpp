#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(Set_Capacity, empty_True) {
  s21::set<int> a = {};
  EXPECT_EQ(a.empty(), 1);
}

TEST(Set_Capacity, empty_False) {
  s21::set<int> a = {1, 2, 3};
  EXPECT_EQ(a.empty(), 0);
}

TEST(Set_Capacity, size) {
  s21::set<int> a = {1, 2, 3};
  EXPECT_EQ(a.size(), 3);
}

TEST(Set_Capacity, max_size) {
  s21::set<int> a = {1, 2, 3};
  EXPECT_EQ(a.max_size(), (s21::set<int>::size_type) - 1);
}