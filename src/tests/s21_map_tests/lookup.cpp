#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(Map_Lookup, contains_True) {
  s21::map<std::string, int> a = {{"a", 1}, {"b", 2}};
  EXPECT_EQ(a.contains("b"), 1);
}

TEST(Map_Lookup, contains_False) {
  s21::map<std::string, int> a = {{"a", 1}, {"b", 2}};
  EXPECT_EQ(a.contains("c"), 0);
}