#include "../include/nbody/Integrate.h"
#include "../include/nbody/System.h"
#include "gtest/gtest.h"

TEST(TestExpectFalse, Positive) {
  EXPECT_FALSE(0 > 1);
}
