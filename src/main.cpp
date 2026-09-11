#include <iostream>
#include <vector>
#include "ShamirSecretSharing/Polynomial.h"
#include "ShamirSecretSharing/FiniteField.h"
#include "ShamirSecretSharing/ShamirSecretSharing.h"

#define PRIME_MODULUS 2147483647 // Example prime modulus for the finite field

int main() {
  int SecretValue = 0;
  int TotalShares = 0;
  int Threshold = 0;

  std::cout << "--- Shamir's Secret Sharing ---\n";

  std::cout << "Enter the secret value (integer): ";
  if (!(std::cin >> SecretValue)) {
    std::cerr << "Error: Invalid input for secret value.\n";
    return 1;
  }

  std::cout << "Enter the total number of shares to generate: ";
  if (!(std::cin >> TotalShares) || TotalShares <= 0) {
    std::cerr << "Error: Invalid input for total shares. Must be greater than 0.\n";
    return 1;
  }

  std::cout << "Enter the threshold (minimum shares required to reconstruct): ";
  if (!(std::cin >> Threshold) || Threshold <= 0 || Threshold > TotalShares) {
    std::cerr << "Error: Invalid input. Threshold must be greater than 0 and less than or equal to total shares.\n";
    return 1;
  }

  std::cout << "\n[+] Generating " << TotalShares << " shares for secret '" 
            << SecretValue << "' with a threshold of " << Threshold << "...\n";

    // Call your library functions here
    // Create a finite field with the specified prime modulus
    shamir_secret_sharing::FiniteField Field(PRIME_MODULUS);
    shamir_secret_sharing::ShamirSecretSharing SSS(Field);
    
    // Create secret share and print the generated shares
    std::vector<shamir_secret_sharing::Share> Shares = SSS.SplitSecret(static_cast<uint64_t>(SecretValue), static_cast<size_t>(Threshold), static_cast<size_t>(TotalShares));
    shamir_secret_sharing::Share SecretShare = {1, static_cast<uint64_t>(SecretValue)};
    
    // Print the generated shares
    for (const auto& share : Shares) {
        std::cout << "[+] Generated share: (" << share.Id << ", " << share.Value << ")\n";
    }

    // Create a subset containing exactly 'Threshold' shares from the generated list
    std::vector<shamir_secret_sharing::Share> thresholdShares(
        Shares.begin(), Shares.begin() + Threshold);

    // Print the shares used for reconstruction
    std::cout << "[+] Using the following shares for reconstruction:\n";
    for (const auto& share : thresholdShares) {
        std::cout << "    (" << share.Id << ", " << share.Value << ")\n";
    }

    // Reconstruct the secret from the shares
    shamir_secret_sharing::Share ReconstructedShare = {1, SSS.ReconstructSecret({thresholdShares})};
    
    // Compare original secret with reconstructed secret
    if (SecretShare.Value == ReconstructedShare.Value) {
        std::cout << "[+] Secret successfully reconstructed: " << ReconstructedShare.Value << "\n";
    } else {
        std::cerr << "[-] Secret reconstruction failed. Original: " << SecretShare.Value 
                  << ", Reconstructed: " << ReconstructedShare.Value << "\n";
    }
    

  std::cout << "[+] Program executed successfully.\n";

  return 0;
}