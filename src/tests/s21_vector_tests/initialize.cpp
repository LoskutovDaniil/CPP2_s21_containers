#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(Vector_Initialize, Default) {
  s21::vector<int> a = s21::vector<int>();
  EXPECT_EQ(a.size(), 0);
}

TEST(Vector_Initialize, Sized) {
  s21::vector<int> a = s21::vector<int>(10);
  EXPECT_EQ(a.size(), 10);
}

TEST(Vector_Initialize, Initializer_List) {
  s21::vector<int> a = {1, 2, 3};
  EXPECT_EQ(a.size(), 3);
}

TEST(Vector_Initialize, Copy) {
  s21::vector<int> a = {1, 2, 3};
  s21::vector<int> b = s21::vector<int>(a);
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(b.size(), 3);
}

TEST(Vector_Initialize, Move) {
  s21::vector<int> a = {1, 2, 3};
  EXPECT_EQ(a.size(), 3);
  s21::vector<int> b = s21::vector<int>((s21::vector<int> &&) a);
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(b.size(), 3);
}

TEST(Vector_Initialize, Move_Operation) {
  s21::vector<int> a = {1, 2, 3};
  EXPECT_EQ(a.size(), 3);
  s21::vector<int> b = s21::vector<int>();
  b = (s21::vector<int> &&) a;
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(b.size(), 3);
}