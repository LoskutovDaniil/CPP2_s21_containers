#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(Stack_Modifiers, push) {
  s21::stack<int> a = {1, 2, 3};
  a.push(4);
  EXPECT_EQ(a.size(), 4);
}

TEST(Stack_Modifiers, pop) {
  s21::stack<int> a = {1, 2, 3};
  a.pop();
  EXPECT_EQ(a.size(), 2);
}

TEST(Stack_Modifiers, swap) {
  s21::stack<int> a = {1, 2, 3};
  s21::stack<int> b = {0};
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(b.size(), 1);
  a.swap(b);
  EXPECT_EQ(a.size(), 1);
  EXPECT_EQ(b.size(), 3);
}

TEST(Stack_Modifiers, insert_many_front) {
  s21::stack<int> a = {1, 2, 3};
  EXPECT_EQ(a.size(), 3);
  a.insert_many_front(4, 5, 6, 7, 8, 9, 0);
  EXPECT_EQ(a.size(), 10);
}