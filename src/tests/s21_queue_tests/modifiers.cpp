#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(Queue_Modifiers, push) {
  s21::queue<int> a = {1, 2, 3};
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(a.back(), 3);
  a.push(4);
  EXPECT_EQ(a.size(), 4);
  EXPECT_EQ(a.back(), 4);
}

TEST(Queue_Modifiers, pop) {
  s21::queue<int> a = {1, 2, 3};
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(a.front(), 1);
  a.pop();
  EXPECT_EQ(a.size(), 2);
  EXPECT_EQ(a.front(), 2);
}

TEST(Queue_Modifiers, swap) {
  s21::queue<int> a = {1, 2, 3};
  s21::queue<int> b = {0};
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(b.size(), 1);
  EXPECT_EQ(a.front(), 1);
  a.swap(b);
  EXPECT_EQ(a.size(), 1);
  EXPECT_EQ(b.size(), 3);
  EXPECT_EQ(a.front(), 0);
}

TEST(Queue_Modifiers, insert_many_back) {
  s21::queue<int> a = {1, 2, 3};
  EXPECT_EQ(a.size(), 3);
  a.insert_many_back(4, 5, 6);
  EXPECT_EQ(a.size(), 6);
}