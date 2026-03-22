#pragma once

namespace fink::core {

class Quantity {
public:
  constexpr Quantity() = default;
  explicit constexpr Quantity(double v) noexcept : value_(v) {}

  [[nodiscard]] constexpr double value() const noexcept { return value_; }

private:
  double value_ = 0.0;
};
} // namespace fink::core
