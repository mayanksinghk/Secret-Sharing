#include "ShamirSecretSharing/ShamirSecretSharing.h"
#include "ShamirSecretSharing/FiniteField.h"
#include "ShamirSecretSharing/Share.h"
#include <gtest/gtest.h>
#include <vector>

namespace {

using namespace shamir_secret_sharing;

class ShamirSecretSharingTest : public ::testing::Test {
protected:
  // Using a large prime for realistic testing (2^31 - 1)
  FiniteField Field{2147483647};
  ShamirSecretSharing Engine{Field};
};

TEST_F(ShamirSecretSharingTest, SplitsAndReconstructsSuccessfully) {
  uint64_t OriginalSecret = 123456789;
  size_t Threshold = 3;
  size_t TotalShares = 5;

  // 1. Split the secret
  std::vector<Share> AllShares = Engine.SplitSecret(OriginalSecret, Threshold, TotalShares);
  EXPECT_EQ(AllShares.size(), TotalShares);

  // 2. Take only a subset of shares (exactly the threshold)
  std::vector<Share> Subset = {AllShares[0], AllShares[2], AllShares[4]};

  // 3. Reconstruct
  uint64_t Reconstructed = Engine.ReconstructSecret(Subset);
  
  EXPECT_EQ(Reconstructed, OriginalSecret);
}

TEST_F(ShamirSecretSharingTest, ReconstructFailsWithInsufficientShares) {
  uint64_t OriginalSecret = 987654321;
  size_t Threshold = 3;
  size_t TotalShares = 5;

  std::vector<Share> AllShares = Engine.SplitSecret(OriginalSecret, Threshold, TotalShares);
  
  // Provide only 2 shares when 3 are required
  std::vector<Share> InsufficientSubset = {AllShares[0], AllShares[1]};

  uint64_t Reconstructed = Engine.ReconstructSecret(InsufficientSubset);
  
  // The math will output a valid integer, but it MUST NOT equal the secret
  EXPECT_NE(Reconstructed, OriginalSecret);
}

TEST_F(ShamirSecretSharingTest, InvalidThresholdThrows) {
    EXPECT_THROW(static_cast<void>(Engine.SplitSecret(42, 5, 3)), std::invalid_argument);
}

} // end anonymous namespace