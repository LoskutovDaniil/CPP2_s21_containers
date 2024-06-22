#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(Vector_Capacity, empty_True) {
  s21::vector<int> a = {};
  EXPECT_EQ(a.empty(), 1);
}

TEST(Vector_Capacity, empty_False) {
  s21::vector<int> a = {1, 2, 3};
  EXPECT_EQ(a.empty(), 0);
}

TEST(Vector_Capacity, size) {
  s21::vector<int> a = {1, 2, 3};
  EXPECT_EQ(a.size(), 3);
}

TEST(Vector_Capacity, max_size) {
  s21::vector<int> a = {1, 2, 3};
  EXPECT_EQ(a.max_size(), (s21::vector<int>::size_type) - 1);
}

TEST(Vector_Capacity, reserve) {
  s21::vector<int> a = {1, 2, 3};
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(a.capacity(), 3);
  a.reserve(10);
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(a.capacity(), 10);
}

TEST(Vector_Capacity, capacity) {
  s21::vector<int> a = {1, 2, 3};
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(a.capacity(), 3);
}

TEST(Vector_Capacity, shrink_to_fit) {
  s21::vector<int> a = {1, 2, 3};
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(a.capacity(), 3);
  a.reserve(10);
  EXPECT_EQ(a.capacity(), 10);
  a.shrink_to_fit();
  EXPECT_EQ(a.capacity(), 3);
}