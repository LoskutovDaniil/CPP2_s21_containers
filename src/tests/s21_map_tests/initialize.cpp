#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(Map_Initialize, Default) {
  s21::map<std::string, int> a = s21::map<std::string, int>();
  EXPECT_EQ(a.size(), 0);
}

TEST(Map_Initialize, Initializer_List) {
  s21::map<std::string, int> a = {{"a", 1}, {"b", 2}};
  EXPECT_EQ(a.size(), 2);
  EXPECT_EQ((*(a.end() - 1)).second, 2);
}

TEST(Map_Initialize, Copy) {
  s21::map<std::string, int> a = {{"a", 1}, {"b", 2}};
  s21::map<std::string, int> b = s21::map<std::string, int>(a);
  EXPECT_EQ(a.size(), 2);
  EXPECT_EQ((*(a.end() - 1)).second, 2);
  EXPECT_EQ(b.size(), 2);
  EXPECT_EQ((*(b.end() - 1)).second, 2);
}

TEST(Map_Initialize, Move) {
  s21::map<std::string, int> a = {{"a", 1}, {"b", 2}};
  s21::map<std::string, int> b =
      s21::map<std::string, int>((s21::map<std::string, int> &&) a);
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(b.size(), 2);
  EXPECT_EQ((*(b.end() - 1)).second, 2);
}

TEST(Map_Initialize, Move_Operation) {
  s21::map<std::string, int> a = {{"a", 1}, {"b", 2}};
  s21::map<std::string, int> b = s21::map<std::string, int>();
  b = (s21::map<std::string, int> &&) a;
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(b.size(), 2);
  EXPECT_EQ((*(b.end() - 1)).second, 2);
}