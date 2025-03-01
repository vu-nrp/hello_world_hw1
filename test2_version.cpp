#include "lib.h"

#include <gtest/gtest.h>

TEST(githubActionsGtestExampleTest, versionTest) {
  EXPECT_TRUE( version() != 0 );
}