#pragma once

#include <fink/core/side.hpp>
#include <fink/core/symbol.hpp>
#include <fink/core/price.hpp>
#include <fink/core/quantity.hpp>
#include <fink/core/timestamp.hpp>

namespace fink::market {

struct TradeTick {
    fink::core::Symbol symbol;
    fink::core::Price price;
    fink::core::Quantity quantity;
    fink::core::Side side;
    fink::core::Timestamp timestamp;
};

} // namespace fink::market