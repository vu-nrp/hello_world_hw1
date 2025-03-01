#include "lib.h"

#include <gtest/gtest.h>

TEST(helloWorldGtest, versionTest) {
  EXPECT_TRUE( version() == 0 );
}
