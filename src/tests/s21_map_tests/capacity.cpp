#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(Map_Capacity, empty_True) {
  s21::map<std::string, int> a = s21::map<std::string, int>();

  EXPECT_EQ(a.empty(), 1);
}

TEST(Map_Capacity, empty_False) {
  s21::map<std::string, int> a = {{"a", 1}, {"b", 2}};

  EXPECT_EQ(a.empty(), 0);
}

TEST(Map_Capacity, size) {
  s21::map<std::string, int> a = {{"a", 1}, {"b", 2}};

  EXPECT_EQ(a.size(), 2);
}

TEST(Map_Capacity, max_size) {
  s21::map<std::string, int> a = {{"a", 1}, {"b", 2}};

  EXPECT_EQ(a.max_size(), (s21::map<std::string, int>::size_type) - 1);
}