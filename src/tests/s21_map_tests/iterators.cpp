#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(Map_Iterators, begin) {
  s21::map<std::string, int> a = {{"a", 1}, {"b", 2}};
  EXPECT_EQ((*a.begin()).first, "a");
}

TEST(Map_Iterators, end) {
  s21::map<std::string, int> a = {{"a", 1}, {"b", 2}};
  EXPECT_EQ((*(a.end() - 1)).first, "b");
}