#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(Set_Initialize, Default) {
  s21::set<int> a = s21::set<int>();
  EXPECT_EQ(a.size(), 0);
}

TEST(Set_Initialize, Initializer_List) {
  s21::set<int> a = {1, 2, 3};
  EXPECT_EQ(a.size(), 3);
}

TEST(Set_Initialize, Copy) {
  s21::set<int> a = {1, 2, 3};
  s21::set<int> b = s21::set<int>(a);
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(b.size(), 3);
  EXPECT_EQ(a.contains(3), 1);
  EXPECT_EQ(b.contains(3), 1);
}

TEST(Set_Initialize, Move) {
  s21::set<int> a = {1, 2, 3};
  s21::set<int> b = s21::set<int>((s21::set<int> &&) a);
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(b.size(), 3);
}

TEST(Set_Initialize, Move_Operation) {
  s21::set<int> a = {1, 2, 3};
  s21::set<int> b = s21::set<int>();
  b = (s21::set<int> &&) a;
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(b.size(), 3);
}