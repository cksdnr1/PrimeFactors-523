#include "prime-factors.cpp"

#include "gmock/gmock.h"

using namespace std;

TEST(PrimeFactors, PrimeTest) { EXPECT_EQ(1, 1); }

int main() {
  ::testing::InitGoogleMock();
  return RUN_ALL_TESTS();
}
