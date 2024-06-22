#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(Map_Access, at_Good) {
  s21::map<std::string, int> a = {{"a", 1}, {"b", 2}};
  EXPECT_EQ(a.at("a"), 1);
}

TEST(Map_Access, at_Bad) {
  s21::map<std::string, int> a = {{"a", 1}, {"b", 2}};
  EXPECT_ANY_THROW(a.at("c"));
}

TEST(Map_Access, at_Operation_Good) {
  s21::map<std::string, int> a = {{"a", 1}, {"b", 2}};
  EXPECT_EQ(a["a"], 1);
}

TEST(Map_Access, at_Operation_Bad) {
  s21::map<std::string, int> a = {{"a", 1}, {"b", 2}};
  a["c"] = 3;
  EXPECT_EQ(a["c"], 3);
}