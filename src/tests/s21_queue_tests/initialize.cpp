#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(Queue_Initialize, Default) {
  s21::queue<int> a = s21::queue<int>();
  EXPECT_EQ(a.size(), 0);
}

TEST(Queue_Initialize, Initializer_List) {
  s21::queue<int> a = {1, 2, 3};
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(a.front(), 1);
}

TEST(Queue_Initialize, Copy) {
  s21::queue<int> a = {1, 2, 3};
  s21::queue<int> b = s21::queue<int>(a);
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(b.size(), 3);
  EXPECT_EQ(a.front(), 1);
  EXPECT_EQ(b.front(), 1);
}

TEST(Queue_Initialize, Move) {
  s21::queue<int> a = {1, 2, 3};
  s21::queue<int> b = s21::queue<int>((s21::queue<int> &&) a);
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(b.size(), 3);
  EXPECT_EQ(b.front(), 1);
}

TEST(Queue_Initialize, Move_Operation) {
  s21::queue<int> a = {1, 2, 3};
  s21::queue<int> b = s21::queue<int>();
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(b.size(), 0);
  EXPECT_EQ(a.front(), 1);
  b = (s21::queue<int> &&) a;
  EXPECT_EQ(b.size(), 3);
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(b.front(), 1);
}