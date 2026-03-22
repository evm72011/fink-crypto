#pragma once

#include <cstdint>

namespace fink::core {

class OrderId {
public:
    constexpr OrderId() = default;
    explicit constexpr OrderId(std::uint64_t v) noexcept : value_(v) {}

    [[nodiscard]] constexpr std::uint64_t value() const noexcept {
        return value_;
    }

private:
    std::uint64_t value_ = 0;
};
}
