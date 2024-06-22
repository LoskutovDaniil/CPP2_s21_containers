#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(List_Access, front) {
  s21::list<int> a = {1, 2, 3};
  EXPECT_EQ(a.front(), 1);
}

TEST(List_Access, back) {
  s21::list<int> a = {1, 2, 3};
  EXPECT_EQ(a.back(), 3);
}