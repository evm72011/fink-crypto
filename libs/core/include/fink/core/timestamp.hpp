#pragma once

#include <cstdint>

namespace fink::core {

class Timestamp {
public:
    constexpr Timestamp() = default;
    explicit constexpr Timestamp(std::int64_t v) noexcept : value_(v) {
    }

    [[nodiscard]] constexpr std::int64_t value() const noexcept {
        return value_;
    }

private:
    std::int64_t value_ = 0;
};
} // namespace fink::core
