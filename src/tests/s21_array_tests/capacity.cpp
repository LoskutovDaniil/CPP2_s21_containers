#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(Array_Capacity, empty_True) {
  s21::array<int, 0> a = s21::array<int, 0>();

  EXPECT_EQ(a.empty(), 1);
}

TEST(Array_Capacity, empty_False) {
  s21::array<int, 2> a = {1, 2};

  EXPECT_EQ(a.empty(), 0);
}

TEST(Array_Capacity, size) {
  s21::array<int, 2> a = {1, 2};

  EXPECT_EQ(a.size(), 2);
}

TEST(Array_Capacity, max_size) {
  s21::array<int, 2> a = {1, 2};

  EXPECT_EQ(a.max_size(), (s21::array<int, 2>::size_type) - 1);
}