#pragma once

#include <cstdint>

namespace shamir_secret_sharing {

/// Handles all modular arithmetic operations over a prime finite field.
class FiniteField {
public:
  /// Initializes the finite field with a specific prime modulus.
  explicit FiniteField(uint64_t PrimeModulus);

  [[nodiscard]] uint64_t Add(uint64_t A, uint64_t B) const;
  [[nodiscard]] uint64_t Subtract(uint64_t A, uint64_t B) const;
  [[nodiscard]] uint64_t Multiply(uint64_t A, uint64_t B) const;
  
  /// Computes the modular inverse of a given value using Fermat's Little Theorem.
  /// Used extensively during Lagrange interpolation.
  [[nodiscard]] uint64_t Invert(uint64_t Value) const;

  [[nodiscard]] uint64_t GetPrime() const;

private:
  uint64_t Prime;
};

} // namespace shamir_secret_sharing
