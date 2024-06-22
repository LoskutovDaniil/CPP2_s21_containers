#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(List_Capacity, empty_True) {
  s21::list<int> a = s21::list<int>();

  EXPECT_EQ(a.empty(), 1);
}

TEST(List_Capacity, empty_False) {
  s21::list<int> a = {1, 2};

  EXPECT_EQ(a.empty(), 0);
}

TEST(List_Capacity, size) {
  s21::list<int> a = {1, 2};

  EXPECT_EQ(a.size(), 2);
}

TEST(List_Capacity, max_size) {
  s21::list<int> a = {1, 2};

  EXPECT_EQ(a.max_size(), (s21::list<int>::size_type) - 1);
}