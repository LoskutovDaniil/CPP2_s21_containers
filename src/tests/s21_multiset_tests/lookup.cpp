#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(Multiset_Lookup, count) {
  s21::multiset<int> a = {1, 2, 2, 3, 4, 5};
  EXPECT_EQ(a.count(2), 2);
}

TEST(Multiset_Lookup, find) {
  s21::multiset<int> a = {1, 2, 2, 3};
  EXPECT_EQ(*(a.find(2)), 2);
}

TEST(Multiset_Lookup, contains_True) {
  s21::multiset<int> a = {1, 2, 3};
  EXPECT_EQ(a.contains(3), 1);
}

TEST(Multiset_Lookup, contains_False) {
  s21::multiset<int> a = {1, 2, 3};
  EXPECT_EQ(a.contains(4), 0);
}

TEST(Multiset_Lookup, equal_range) {
  s21::multiset<int> a = {1, 2, 2, 2, 3};
  std::pair<s21::multiset<int>::iterator, s21::multiset<int>::iterator>
      iter_pair = a.equal_range(2);
  size_t counter = 0;
  for (auto i = iter_pair.first; i != iter_pair.second; ++i) {
    EXPECT_EQ(*i, 2);
    ++counter;
  }
  EXPECT_EQ(counter, 3);
}

TEST(Multiset_Lookup, lower_bound) {
  s21::multiset<int> a = {1, 2, 2, 2, 3};
  EXPECT_EQ(*a.lower_bound(2), 2);
}

TEST(Multiset_Lookup, upper_bound) {
  s21::multiset<int> a = {1, 2, 2, 2, 3};
  EXPECT_EQ(*a.upper_bound(2), 3);
}