#pragma once

#include "price.hpp"
#include "quantity.hpp"
#include "timestamp.hpp"
#include "symbol.hpp"

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