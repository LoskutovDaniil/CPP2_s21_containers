#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(Vector_Modifiers, clear) {
  s21::vector<int> a = {1, 2, 3};
  a.clear();
  EXPECT_EQ(a.size(), 0);
}

TEST(Vector_Modifiers, insert) {
  s21::vector<int> a = {1, 2, 3};
  a.insert(a.begin(), 0);
  EXPECT_EQ(a.size(), 4);
}

TEST(Vector_Modifiers, erase) {
  s21::vector<int> a = {1, 2, 3};
  a.erase(a.begin());
  EXPECT_EQ(a.size(), 2);
}

TEST(Vector_Modifiers, push_back) {
  s21::vector<int> a = {1, 2, 3};
  a.push_back(4);
  EXPECT_EQ(a.size(), 4);
}

TEST(Vector_Modifiers, pop_back) {
  s21::vector<int> a = {1, 2, 3};
  a.pop_back();
  EXPECT_EQ(a.size(), 2);
}

TEST(Vector_Modifiers, swap) {
  s21::vector<int> a = {1, 2, 3};
  s21::vector<int> b = {0};
  a.swap(b);
  EXPECT_EQ(a.size(), 1);
  EXPECT_EQ(b.size(), 3);
}

TEST(Vector_Modifiers, insert_many) {
  s21::vector<int> a = {1, 2, 3};
  a.insert_many(a.begin(), -3, -2, -1, 0);
  EXPECT_EQ(a.size(), 7);
}

TEST(Vector_Modifiers, insert_many_back) {
  s21::vector<int> a = {1, 2, 3};
  a.insert_many_back(4, 5, 6, 7);
  EXPECT_EQ(a.size(), 7);
}