#pragma once

#include <string>

namespace fink::core {

class Symbol {
public:
    Symbol() : value_() {
    }

    explicit Symbol(std::string value) : value_(std::move(value)) {
    }

    [[nodiscard]] const std::string &value() const noexcept {
        return value_;
    }

private:
    std::string value_;
};

} // namespace fink::core
