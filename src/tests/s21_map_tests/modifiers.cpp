#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(Map_Modifiers, clear) {
  s21::map<std::string, int> a = {{"a", 1}, {"b", 2}};
  EXPECT_EQ(a.size(), 2);
  a.clear();
  EXPECT_EQ(a.size(), 0);
}

TEST(Map_Modifiers, insert_Pair_True) {
  s21::map<std::string, int> a = {{"a", 1}, {"b", 2}};
  EXPECT_EQ(a.size(), 2);
  EXPECT_EQ(a.insert({"c", 3}).second, 1);
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(a["c"], 3);
}

TEST(Map_Modifiers, insert_True) {
  s21::map<std::string, int> a = {{"a", 1}, {"b", 2}};
  EXPECT_EQ(a.size(), 2);
  EXPECT_EQ(a.insert("c", 3).second, 1);
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(a["c"], 3);
}

TEST(Map_Modifiers, insert_or_assign_True) {
  s21::map<std::string, int> a = {{"a", 1}, {"b", 2}};
  EXPECT_EQ(a.size(), 2);
  EXPECT_EQ(a.insert_or_assign("c", 3).second, 1);
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(a["c"], 3);
}

TEST(Map_Modifiers, insert_Pair_False) {
  s21::map<std::string, int> a = {{"a", 1}, {"b", 2}};
  EXPECT_EQ(a.size(), 2);
  EXPECT_EQ(a.insert({"b", 3}).second, 0);
  EXPECT_EQ(a.size(), 2);
}

TEST(Map_Modifiers, insert_False) {
  s21::map<std::string, int> a = {{"a", 1}, {"b", 2}};
  EXPECT_EQ(a.size(), 2);
  EXPECT_EQ(a.insert("b", 3).second, 0);
  EXPECT_EQ(a.size(), 2);
}

TEST(Map_Modifiers, insert_or_assign_False) {
  s21::map<std::string, int> a = {{"a", 1}, {"b", 2}};
  EXPECT_EQ(a.size(), 2);
  EXPECT_EQ(a.insert_or_assign("b", 3).second, 0);
  EXPECT_EQ(a.size(), 2);
  EXPECT_EQ(a["b"], 3);
}

TEST(Map_Modifiers, erase) {
  s21::map<std::string, int> a = {{"a", 1}, {"b", 2}};
  EXPECT_EQ(a.size(), 2);
  a.erase(a.begin());
  EXPECT_EQ(a.size(), 1);
}

TEST(Map_Modifiers, swap) {
  s21::map<std::string, int> a = {{"a", 1}, {"b", 2}};
  s21::map<std::string, int> b = s21::map<std::string, int>();
  EXPECT_EQ(a.size(), 2);
  EXPECT_EQ(b.size(), 0);
  a.swap(b);
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(b.size(), 2);
}

TEST(Map_Modifiers, merge) {
  s21::map<std::string, int> a = {{"a", 1}, {"b", 2}};
  s21::map<std::string, int> b = {{"c", 3}};
  EXPECT_EQ(a.size(), 2);
  a.merge(b);
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(a["c"], 3);
}

TEST(Map_Modifiers, insert_many) {
  s21::map<std::string, int> a = {{"a", 1}, {"b", 2}};
  EXPECT_EQ(a.size(), 2);
  a.insert_many(std::pair<std::string, int>("c", 3),
                std::pair<std::string, int>("d", 4),
                std::pair<std::string, int>("e", 5));
  EXPECT_EQ(a.size(), 5);
}