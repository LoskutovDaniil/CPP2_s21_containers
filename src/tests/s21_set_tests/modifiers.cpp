#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(Set_Modifiers, clear) {
  s21::set<int> a = {1, 2, 3};
  EXPECT_EQ(a.size(), 3);
  a.clear();
  EXPECT_EQ(a.size(), 0);
}

TEST(Set_Modifiers, insert_True) {
  s21::set<int> a = {1, 2, 3};
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(a.insert(4).second, 1);
  EXPECT_EQ(a.size(), 4);
}

TEST(Set_Modifiers, insert_False) {
  s21::set<int> a = {1, 2, 3};
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(a.insert(3).second, 0);
  EXPECT_EQ(a.size(), 3);
}

TEST(Set_Modifiers, erase) {
  s21::set<int> a = {1, 2, 3};
  a.erase(a.begin());
  EXPECT_EQ(a.size(), 2);
}

TEST(Set_Modifiers, swap) {
  s21::set<int> a = {1, 2, 3};
  s21::set<int> b = {1};
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(b.size(), 1);
  a.swap(b);
  EXPECT_EQ(a.size(), 1);
  EXPECT_EQ(b.size(), 3);
}

TEST(Set_Modifiers, merge) {
  s21::set<int> a = {1, 2};
  s21::set<int> b = {3};
  EXPECT_EQ(a.size(), 2);
  a.merge(b);
  EXPECT_EQ(a.size(), 3);
}

TEST(Set_Modifiers, insert_many) {
  s21::set<int> a = {1, 2, 3};
  EXPECT_EQ(a.size(), 3);
  a.insert_many(4, 5, 6, 7, 8, 9, 0);
  EXPECT_EQ(a.size(), 10);
}