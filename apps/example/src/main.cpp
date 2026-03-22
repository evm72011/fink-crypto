#include <fink/core/symbol.hpp>
#include <fink/market/book_snapshot.hpp>
#include <iostream>

#include <cassert>

int main() {
    std::cout << "Hello, fink-crypto-example\n";

    // clang-format off
    fink::market::BookSnapshot snapshot{
        .symbol = fink::core::Symbol{"BTCUSDT"},
        .timestamp = fink::core::Timestamp{123456789},
        .bids = {},
        .asks = {}
    };
    // clang-format on

    assert(snapshot.bids.empty());
    assert(snapshot.asks.empty());
}
