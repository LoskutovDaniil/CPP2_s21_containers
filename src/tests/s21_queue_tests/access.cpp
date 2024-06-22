#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(Queue_Access, front) {
  s21::queue<int> a = {1, 2, 3};
  EXPECT_EQ(a.front(), 1);
}

TEST(Queue_Access, back) {
  s21::queue<int> a = {1, 2, 3};
  EXPECT_EQ(a.back(), 3);
}