#include "ShamirSecretSharing/FiniteField.h"
#include <stdexcept>

namespace shamir_secret_sharing {

FiniteField::FiniteField(uint64_t PrimeModulus) : Prime(PrimeModulus) {
  if (PrimeModulus < 2) {
    throw std::invalid_argument("Prime modulus must be at least 2.");
  }
}

uint64_t FiniteField::Add(uint64_t A, uint64_t B) const {
  return (A % Prime + B % Prime) % Prime;
}

uint64_t FiniteField::Subtract(uint64_t A, uint64_t B) const {
  // Add Prime before subtracting to prevent unsigned integer underflow
  return (A % Prime + Prime - (B % Prime)) % Prime;
}

uint64_t FiniteField::Multiply(uint64_t A, uint64_t B) const {
  // Cast to 128-bit integer to prevent overflow during multiplication
  return static_cast<uint64_t>((static_cast<__uint128_t>(A) * B) % Prime);
}

uint64_t FiniteField::Invert(uint64_t Value) const {
  if (Value % Prime == 0) {
    throw std::invalid_argument("Zero does not have a modular inverse.");
  }

  // Fermat's Little Theorem: a^(p-2) mod p
  uint64_t Result = 1;
  uint64_t Base = Value % Prime;
  uint64_t Exponent = Prime - 2;

  while (Exponent > 0) {
    if (Exponent % 2 == 1) {
      Result = Multiply(Result, Base);
    }
    Base = Multiply(Base, Base);
    Exponent /= 2;
  }

  return Result;
}

uint64_t FiniteField::GetPrime() const { 
  return Prime; 
}

} // namespace shamir_secret_sharing