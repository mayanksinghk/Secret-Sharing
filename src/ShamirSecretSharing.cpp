#include "ShamirSecretSharing/ShamirSecretSharing.h"
#include "ShamirSecretSharing/Polynomial.h"
#include <stdexcept>

namespace shamir_secret_sharing {

ShamirSecretSharing::ShamirSecretSharing(const FiniteField &Field) : Field(Field) {}

std::vector<Share> ShamirSecretSharing::SplitSecret(uint64_t Secret,
                                                    size_t Threshold,
                                                    size_t TotalShares) const {
  if (Threshold > TotalShares) {
    throw std::invalid_argument("Threshold cannot be greater than TotalShares.");
  }
  if (Threshold == 0) {
    throw std::invalid_argument("Threshold must be at least 1.");
  }

  Polynomial Poly(Secret, Threshold, Field);
  std::vector<Share> Shares;
  Shares.reserve(TotalShares);

  for (uint64_t I = 1; I <= TotalShares; ++I) {
    Shares.push_back({I, Poly.Evaluate(I)});
  }

  return Shares;
}

uint64_t ShamirSecretSharing::ReconstructSecret(const std::vector<Share> &Shares) const {
  if (Shares.empty()) {
    throw std::invalid_argument("Cannot reconstruct a secret from zero shares.");
  }

  uint64_t ReconstructedSecret = 0;

  for (size_t I = 0; I < Shares.size(); ++I) {
    uint64_t Numerator = 1;
    uint64_t Denominator = 1;

    for (size_t J = 0; J < Shares.size(); ++J) {
      if (I == J) {
        continue;
      }

      uint64_t Xi = Shares[I].Id;
      uint64_t Xj = Shares[J].Id;

      // Numerator = Numerator * (0 - Xj)
      uint64_t NegativeXj = Field.Subtract(0, Xj);
      Numerator = Field.Multiply(Numerator, NegativeXj);

      // Denominator = Denominator * (Xi - Xj)
      uint64_t Difference = Field.Subtract(Xi, Xj);
      Denominator = Field.Multiply(Denominator, Difference);
    }

    // Lagrange Basis Polynomial l_i(0)
    uint64_t LagrangeBasis = Field.Multiply(Numerator, Field.Invert(Denominator));
    
    // y_i * l_i(0)
    uint64_t Term = Field.Multiply(Shares[I].Value, LagrangeBasis);
    
    ReconstructedSecret = Field.Add(ReconstructedSecret, Term);
  }

  return ReconstructedSecret;
}

} // namespace shamir_secret_sharing