#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(Multiset_Capacity, empty_True) {
  s21::multiset<int> a = s21::multiset<int>();

  EXPECT_EQ(a.empty(), 1);
}

TEST(Multiset_Capacity, empty_False) {
  s21::multiset<int> a = {1, 2};

  EXPECT_EQ(a.empty(), 0);
}

TEST(Multiset_Capacity, size) {
  s21::multiset<int> a = {1, 2};

  EXPECT_EQ(a.size(), 2);
}

TEST(Multiset_Capacity, max_size) {
  s21::multiset<int> a = {1, 2};

  EXPECT_EQ(a.max_size(), (s21::multiset<int>::size_type) - 1);
}