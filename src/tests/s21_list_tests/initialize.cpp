#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(List_Iinitialize, Default) {
  s21::list<int> a = s21::list<int>();
  EXPECT_EQ(a.size(), 0);
}

TEST(List_Iinitialize, Initializer_List) {
  s21::list<int> a = {1, 2, 3};
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(a.front(), 1);
}

TEST(List_Iinitialize, Copy) {
  s21::list<int> a = {1, 2, 3};
  s21::list<int> b = a;
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(b.size(), 3);
  EXPECT_EQ(a.front(), 1);
  EXPECT_EQ(b.front(), 1);
}

TEST(List_Iinitialize, Move) {
  s21::list<int> a = {1, 2, 3};
  s21::list<int> b = s21::list<int>((s21::list<int> &&) a);
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(b.size(), 3);
  EXPECT_EQ(b.front(), 1);
}

TEST(List_Iinitialize, Move_Operation) {
  s21::list<int> a = {1, 2, 3};
  s21::list<int> b = {1, 2, 3};
  b = (s21::list<int> &&) a;
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(b.size(), 3);
  EXPECT_EQ(b.front(), 1);
}