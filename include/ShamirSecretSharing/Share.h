#pragma once

#include <cstdint>

namespace shamir_secret_sharing {

/// Represents a single evaluated point on the polynomial graph.
struct Share {
  /// The X-coordinate (must be > 0). Represents the participant's unique ID.
  uint64_t Id;

  /// The Y-coordinate. The evaluated result of f(Id) modulo the prime field.
  uint64_t Value;
};

} // namespace shamir_secret_sharing