#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(List_Modifiers, clear) {
  s21::list<int> a = {1, 2, 3};
  a.clear();
  EXPECT_EQ(a.size(), 0);
}

TEST(List_Modifiers, insert) {
  s21::list<int> a = {1, 2, 3};
  a.insert(a.begin() + 1, 4);
  EXPECT_EQ(a.size(), 4);
  EXPECT_EQ(*(a.begin() + 1), 4);
}

TEST(List_Modifiers, erase) {
  s21::list<int> a = {1, 2, 3};
  a.erase(a.begin());
  EXPECT_EQ(a.size(), 2);
  EXPECT_EQ(*a.begin(), 2);
}

TEST(List_Modifiers, push_back) {
  s21::list<int> a = {1, 2, 3};
  a.push_back(4);
  EXPECT_EQ(a.size(), 4);
  EXPECT_EQ(a.back(), 4);
}

TEST(List_Modifiers, pop_back) {
  s21::list<int> a = {1, 2, 3};
  a.pop_back();
  EXPECT_EQ(a.size(), 2);
  EXPECT_EQ(a.back(), 2);
}

TEST(List_Modifiers, push_front) {
  s21::list<int> a = {1, 2, 3};
  a.push_front(0);
  EXPECT_EQ(a.size(), 4);
  EXPECT_EQ(a.front(), 0);
}

TEST(List_Modifiers, pop_front) {
  s21::list<int> a = {1, 2, 3};
  a.pop_front();
  EXPECT_EQ(a.size(), 2);
  EXPECT_EQ(a.front(), 2);
}

TEST(List_Modifiers, swap) {
  s21::list<int> a = {1, 2, 3};
  s21::list<int> b = {4, 5, 6, 7};
  a.swap(b);
  EXPECT_EQ(a.size(), 4);
  EXPECT_EQ(b.size(), 3);
  EXPECT_EQ(a.front(), 4);
  EXPECT_EQ(b.front(), 1);
}

TEST(List_Modifiers, merge) {
  s21::list<int> a = {1, 2, 3};
  s21::list<int> b = {7, 5, 6, 4};
  a.merge(b);
  EXPECT_EQ(a.size(), 7);
  EXPECT_EQ(a.front(), 1);
  EXPECT_EQ(a.back(), 7);
}

TEST(List_Modifiers, splice) {
  s21::list<int> a = {1, 2, 3};
  s21::list<int> b = {4};
  a.splice(a.begin() + 1, b);
  EXPECT_EQ(a.size(), 4);
  EXPECT_EQ(a.front(), 1);
  EXPECT_EQ(a.back(), 3);
}

TEST(List_Modifiers, reverse) {
  s21::list<int> a = {1, 2, 3};
  a.reverse();
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(a.front(), 3);
  EXPECT_EQ(a.back(), 1);
}

TEST(List_Modifiers, unique) {
  s21::list<int> a = {1, 2, 3, 3, 4, 5, 6, 4};
  a.unique();
  EXPECT_EQ(a.size(), 7);
  EXPECT_EQ(a.front(), 1);
  EXPECT_EQ(a.back(), 4);
}

TEST(List_Modifiers, sort) {
  s21::list<int> a = {1, 3, 0, 7, -5};
  a.sort();
  EXPECT_EQ(a.size(), 5);
  EXPECT_EQ(a.front(), -5);
  EXPECT_EQ(a.back(), 7);
}

TEST(List_Modifiers, insert_many) {
  s21::list<int> a = {1};
  a.insert_many(a.begin() + 1, 2, 3, 4, 5);
  EXPECT_EQ(a.size(), 5);
  EXPECT_EQ(a.front(), 1);
  EXPECT_EQ(a.back(), 5);
}

TEST(List_Modifiers, insert_many_back) {
  s21::list<int> a = {1};
  a.insert_many_back(2, 3, 4, 5);
  EXPECT_EQ(a.size(), 5);
  EXPECT_EQ(a.front(), 1);
  EXPECT_EQ(a.back(), 5);
}

TEST(List_Modifiers, insert_many_front) {
  s21::list<int> a = {1};
  a.insert_many_front(-5, -4, -3, -2, -1, 0);
  EXPECT_EQ(a.size(), 7);
  EXPECT_EQ(a.front(), -5);
  EXPECT_EQ(a.back(), 1);
}