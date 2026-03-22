#pragma once

#include "fink/core/price.hpp"
#include "fink/core/quantity.hpp"
#include "fink/core/side.hpp"
#include "fink/core/symbol.hpp"
#include "fink/core/timestamp.hpp"

namespace fink::core {

struct Trade {
    Symbol symbol;
    Price price;
    Quantity quantity;
    Side side;
    Timestamp timestamp;
};

} // namespace fink::core