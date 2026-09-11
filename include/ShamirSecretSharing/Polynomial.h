#pragma once 

#include "ShamirSecretSharing/FiniteField.h"
#include <cstddef>
#include <cstdint>
#include <vector>

namespace shamir_secret_sharing {

/// Represents a mathematical polynomial defined over a finite field.
class Polynomial {
public:
  /// Constructs a polynomial of degree (Threshold - 1).
  /// The constant term (Coefficient[0]) is strictly set to the Secret.
  Polynomial(uint64_t Secret, size_t Threshold, const FiniteField &Field);

  /// Evaluates the polynomial at a given X coordinate.
  [[nodiscard]] uint64_t Evaluate(uint64_t X) const;

  [[nodiscard]] size_t GetDegree() const;

private:
  std::vector<uint64_t> Coefficients;
  const FiniteField &Field;
};

} // namespace shamir_secret_sharing
