#pragma once

#include <optional>

#include <fink/core/price.hpp>
#include <fink/core/quantity.hpp>

namespace fink::orderbook {

struct BookTopLevel {
    fink::core::Price price;
    fink::core::Quantity quantity;
};

struct BookTop {
    std::optional<BookTopLevel> best_bid;
    std::optional<BookTopLevel> best_ask;
};

} // namespace fink::orderbook