#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(Array_Iinitialize, Default) {
  s21::array<int, 10> a = s21::array<int, 10>();
  EXPECT_EQ(a.size(), 10);
}

TEST(Array_Iinitialize, Initializer_List) {
  s21::array<int, 3> a = {1, 2, 3};
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(a[0], 1);
}

TEST(Array_Iinitialize, Copy) {
  s21::array<int, 3> a = {1, 2, 3};
  s21::array<int, 3> b = a;
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(b.size(), 3);
  EXPECT_EQ(a[0], 1);
  EXPECT_EQ(b[0], 1);
}

TEST(Array_Iinitialize, Move) {
  s21::array<int, 3> a = {1, 2, 3};
  s21::array<int, 3> b = (s21::array<int, 3> &&) a;
  EXPECT_EQ(a.data() == nullptr, 1);
  EXPECT_EQ(b.data() != nullptr, 1);
  EXPECT_EQ(b[0], 1);
}

TEST(Array_Iinitialize, Move_Operation) {
  s21::array<int, 3> a = {1, 2, 3};
  s21::array<int, 3> b = {1, 2, 3};
  b = (s21::array<int, 3> &&) a;
  EXPECT_EQ(a.data() == nullptr, 1);
  EXPECT_EQ(b.data() != nullptr, 1);
  EXPECT_EQ(b[0], 1);
}