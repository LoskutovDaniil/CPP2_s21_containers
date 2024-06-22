#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(Multiset_Modifiers, clear) {
  s21::multiset<int> a = {1, 2};
  a.clear();
  EXPECT_EQ(a.size(), 0);
}

TEST(Multiset_Modifiers, insert) {
  s21::multiset<int> a = {1, 2};
  EXPECT_EQ(*(a.insert(3)), 3);
  EXPECT_EQ(a.size(), 3);
}

TEST(Multiset_Modifiers, erase) {
  s21::multiset<int> a = {1, 2};
  a.erase(a.begin());
  EXPECT_EQ(a.size(), 1);
}

TEST(Multiset_Modifiers, swap) {
  s21::multiset<int> a = {1, 2};
  s21::multiset<int> b = s21::multiset<int>();
  EXPECT_EQ(a.size(), 2);
  EXPECT_EQ(b.size(), 0);
  a.swap(b);
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(b.size(), 2);
}

TEST(Multiset_Modifiers, merge) {
  s21::multiset<int> a = {1, 2};
  s21::multiset<int> b = {3};
  EXPECT_EQ(a.size(), 2);
  a.merge(b);
  EXPECT_EQ(a.size(), 3);
}

TEST(Multiset_Modifiers, insert_many) {
  s21::multiset<int> a = {1, 2};
  EXPECT_EQ(a.size(), 2);
  a.insert_many(0, 3, 4, 5, 6, 7, 8, 9);
  EXPECT_EQ(a.size(), 10);
}