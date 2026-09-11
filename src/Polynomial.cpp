#include "ShamirSecretSharing/Polynomial.h"
#include <random>
#include <stdexcept>

namespace shamir_secret_sharing {

Polynomial::Polynomial(uint64_t Secret, size_t Threshold, const FiniteField &Field)
    : Field(Field) {
  if (Threshold == 0) {
    throw std::invalid_argument("Threshold must be at least 1.");
  }

  Coefficients.reserve(Threshold);
  
  // f(0) is always the secret
  Coefficients.push_back(Secret % Field.GetPrime());

  // Note: std::mt19937_64 is used here for demonstration.
  // In a production environment, replace this with a CSPRNG (e.g., OpenSSL RAND_bytes).
  std::random_device RandomDevice;
  std::mt19937_64 Generator(RandomDevice());
  std::uniform_int_distribution<uint64_t> Distribution(1, Field.GetPrime() - 1);

  // Generate random coefficients for terms x^1 to x^(Threshold-1)
  for (size_t I = 1; I < Threshold; ++I) {
    Coefficients.push_back(Distribution(Generator));
  }
}

uint64_t Polynomial::Evaluate(uint64_t X) const {
  uint64_t Result = 0;
  
  // Horner's Method: efficiently evaluates the polynomial without computing large powers
  for (auto It = Coefficients.rbegin(); It != Coefficients.rend(); ++It) {
    Result = Field.Add(Field.Multiply(Result, X), *It);
  }
  
  return Result;
}

size_t Polynomial::GetDegree() const {
  return Coefficients.empty() ? 0 : Coefficients.size() - 1;
}

} // namespace shamir_secret_sharing