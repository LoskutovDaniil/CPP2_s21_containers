#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(Array_Access, at_Good) {
  s21::array<int, 1> a = {1};

  EXPECT_EQ(a.at(0), 1);
}

TEST(Array_Access, at_Bad) {
  s21::array<int, 1> a = {1};

  EXPECT_ANY_THROW(a.at(1));
}

TEST(Array_Access, at_Operation_Good) {
  s21::array<int, 1> a = {1};

  EXPECT_EQ(a[0], 1);
}

TEST(Array_Access, at_Operation_Bad) {
  s21::array<int, 1> a = {1};

  EXPECT_ANY_THROW(a[1]);
}

TEST(Array_Access, front) {
  s21::array<int, 2> a = {1, 2};

  EXPECT_EQ(a.front(), 1);
}

TEST(Array_Access, back) {
  s21::array<int, 2> a = {1, 2};

  EXPECT_EQ(a.back(), 2);
}

TEST(Array_Access, data) {
  s21::array<int, 1> a = {1};

  EXPECT_EQ(a.data()[0], 1);
}