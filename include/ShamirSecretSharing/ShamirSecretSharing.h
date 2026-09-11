#pragma once 

#include "ShamirSecretSharing/FiniteField.h"
#include "ShamirSecretSharing/Share.h"
#include <cstddef>
#include <cstdint>
#include <vector>

namespace shamir_secret_sharing {

/// The core protocol engine for splitting and reconstructing secrets.
class ShamirSecretSharing {
public:
  explicit ShamirSecretSharing(const FiniteField &Field);

  /// Splits a secret into a specified number of shares.
  /// \param Secret The integer value to protect.
  /// \param Threshold The minimum number of shares required for reconstruction.
  /// \param TotalShares The total number of shares to generate.
  /// \return A vector containing all generated Shares.
  [[nodiscard]] std::vector<Share> SplitSecret(uint64_t Secret, 
                                               size_t Threshold,
                                               size_t TotalShares) const;

  /// Reconstructs the original secret from a subset of shares.
  /// \param Shares A vector of available shares (must be >= Threshold).
  /// \return The reconstructed secret integer.
  [[nodiscard]] uint64_t ReconstructSecret(const std::vector<Share> &Shares) const;

private:
  const FiniteField &Field;
};

} // namespace shamir_secret_sharing