#include "ShamirSecretSharing/Polynomial.h"
#include "ShamirSecretSharing/FiniteField.h"
#include <gtest/gtest.h>

namespace {

using namespace shamir_secret_sharing;

TEST(PolynomialTest, EvaluatesSecretAtZero) {
  FiniteField Field(257);
  uint64_t Secret = 42;
  size_t Threshold = 3;

  Polynomial Poly(Secret, Threshold, Field);

  // By definition, f(0) MUST equal the secret
  EXPECT_EQ(Poly.Evaluate(0), Secret);
}

TEST(PolynomialTest, ZeroThresholdThrowsException) {
  FiniteField Field(257);
  EXPECT_THROW(Polynomial(42, 0, Field), std::invalid_argument);
}

} // end anonymous namespace