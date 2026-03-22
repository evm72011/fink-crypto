#pragma once

#include "price.hpp"
#include "quantity.hpp"
#include "timestamp.hpp"
#include "side.hpp"
#include "symbol.hpp"

namespace fink::core {

struct Trade {
    Symbol symbol;
    Price price;
    Quantity quantity;
    Side side;
    Timestamp timestamp;
};

}