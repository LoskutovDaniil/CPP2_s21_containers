#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(Stack_Access, top) {
  s21::stack<int> a = {1};
  EXPECT_EQ(a.top(), 1);
}