#pragma once

#include <cstdint>

namespace fink::core {

class Price {
public:
  constexpr Price() = default;
  explicit constexpr Price(double v) noexcept : value_(v) {}

  [[nodiscard]] constexpr double value() const noexcept { return value_; }

private:
  double value_ = 0.0;
};

} // namespace fink::core