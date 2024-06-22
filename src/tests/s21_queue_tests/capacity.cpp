#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(Queue_Capacity, empty_True) {
  s21::queue<int> a = {};
  EXPECT_EQ(a.empty(), 1);
}

TEST(Queue_Capacity, empty_False) {
  s21::queue<int> a = {1, 2, 3};
  EXPECT_EQ(a.empty(), 0);
}

TEST(Queue_Capacity, size) {
  s21::queue<int> a = {1, 2, 3};
  EXPECT_EQ(a.size(), 3);
}