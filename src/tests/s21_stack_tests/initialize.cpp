#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(Stack_Initialize, Default) {
  s21::stack<int> a = s21::stack<int>();
  EXPECT_EQ(a.size(), 0);
}

TEST(Stack_Initialize, Initializer_List) {
  s21::stack<int> a = {1, 2, 3};
  EXPECT_EQ(a.size(), 3);
}

TEST(Stack_Initialize, Copy) {
  s21::stack<int> a = {1, 2, 3};
  s21::stack<int> b = s21::stack<int>(a);
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(b.size(), 3);
}

TEST(Stack_Initialize, Move) {
  s21::stack<int> a = {1, 2, 3};
  s21::stack<int> b = s21::stack<int>((s21::stack<int> &&) a);
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(b.size(), 3);
}

TEST(Stack_Initialize, Move_Operation) {
  s21::stack<int> a = {1, 2, 3};
  s21::stack<int> b = s21::stack<int>();
  b = (s21::stack<int> &&) a;
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(b.size(), 3);
}