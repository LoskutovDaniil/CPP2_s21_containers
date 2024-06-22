#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(Array_Modifiers, swap) {
  s21::array<int, 2> a = {1, 2};
  s21::array<int, 2> b = {2, 1};

  EXPECT_EQ(a[0], 1);
  EXPECT_EQ(b[0], 2);

  a.swap(b);

  EXPECT_EQ(a[0], 2);
  EXPECT_EQ(b[0], 1);
}

TEST(Array_Modifiers, fill) {
  s21::array<int, 3> a = {1, 2, 3};

  EXPECT_EQ(a[0], 1);
  EXPECT_EQ(a[1], 2);
  EXPECT_EQ(a[2], 3);

  a.fill(0);

  EXPECT_EQ(a[0], 0);
  EXPECT_EQ(a[1], 0);
  EXPECT_EQ(a[2], 0);
}