#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(Multiset_Initialize, Default) {
  s21::multiset<int> a = s21::multiset<int>();
  EXPECT_EQ(a.size(), 0);
}

TEST(Multiset_Initialize, Initializer_List) {
  s21::multiset<int> a = {1, 2};
  EXPECT_EQ(a.size(), 2);
  EXPECT_EQ(*(a.end() - 1), 2);
}

TEST(Multiset_Initialize, Copy) {
  s21::multiset<int> a = {1, 2};
  s21::multiset<int> b = s21::multiset<int>(a);
  EXPECT_EQ(a.size(), 2);
  EXPECT_EQ(*(a.end() - 1), 2);
  EXPECT_EQ(b.size(), 2);
  EXPECT_EQ(*(a.end() - 1), 2);
}

TEST(Multiset_Initialize, Move) {
  s21::multiset<int> a = {1, 2};
  s21::multiset<int> b = s21::multiset<int>((s21::multiset<int> &&) a);
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(b.size(), 2);
}

TEST(Multiset_Initialize, Move_Operation) {
  s21::multiset<int> a = {1, 2};
  s21::multiset<int> b = s21::multiset<int>();
  b = (s21::multiset<int> &&) a;
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(b.size(), 2);
}