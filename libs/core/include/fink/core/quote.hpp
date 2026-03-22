#pragma once

#include "fink/core/price.hpp"
#include "fink/core/quantity.hpp"
#include "fink/core/timestamp.hpp"
#include "fink/core/symbol.hpp"

namespace fink::core {

struct Quote {
    Symbol symbol;

    Price bid_price;
    Quantity bid_quantity;

    Price ask_price;
    Quantity ask_quantity;

    Timestamp timestamp;
};

}