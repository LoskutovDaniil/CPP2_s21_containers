#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(Vector_Access, at_Good) {
  s21::vector<int> a = {1, 2, 3};
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(a.at(0), 1);
}

TEST(Vector_Access, at_Bad) {
  s21::vector<int> a = {1, 2, 3};
  EXPECT_EQ(a.size(), 3);
  EXPECT_ANY_THROW(a.at(3));
}

TEST(Vector_Access, at_Operation_Good) {
  s21::vector<int> a = {1, 2, 3};
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(a[0], 1);
}

TEST(Vector_Access, at_Operation_Bad) {
  s21::vector<int> a = {1, 2, 3};
  EXPECT_EQ(a.size(), 3);
  EXPECT_ANY_THROW(a[3]);
}

TEST(Vector_Access, front) {
  s21::vector<int> a = {1, 2, 3};
  EXPECT_EQ(a.front(), 1);
}

TEST(Vector_Access, back) {
  s21::vector<int> a = {1, 2, 3};
  EXPECT_EQ(a.back(), 3);
}

TEST(Vector_Access, data) {
  s21::vector<int> a = {1, 2, 3};
  EXPECT_EQ(*(a.data()), 1);
}