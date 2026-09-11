#include "ShamirSecretSharing/FiniteField.h"
#include <gtest/gtest.h>
#include <stdexcept>

namespace {

using namespace shamir_secret_sharing;

class FiniteFieldTest : public ::testing::Test {
protected:
  // Using a small prime (257) for predictable testing
  FiniteField Field{257};
};

TEST_F(FiniteFieldTest, AdditionWrapsCorrectly) {
  EXPECT_EQ(Field.Add(100, 200), 43); // 300 % 257 = 43
  EXPECT_EQ(Field.Add(257, 10), 10);
}

TEST_F(FiniteFieldTest, SubtractionPreventsUnderflow) {
  EXPECT_EQ(Field.Subtract(10, 20), 247); // (10 - 20) mod 257 = -10 = 247
  EXPECT_EQ(Field.Subtract(100, 100), 0);
}

TEST_F(FiniteFieldTest, MultiplicationWrapsCorrectly) {
  EXPECT_EQ(Field.Multiply(10, 30), 43); // 300 % 257 = 43
}

TEST_F(FiniteFieldTest, ModularInverseCalculatesCorrectly) {
  // 10 * 180 = 1800. 1800 % 257 = 1.
  EXPECT_EQ(Field.Invert(10), 180);
}

TEST_F(FiniteFieldTest, InvertingZeroThrowsException) {
    EXPECT_THROW(static_cast<void>(Field.Invert(0)), std::invalid_argument);
}

} // end anonymous namespace