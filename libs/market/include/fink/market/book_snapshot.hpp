#pragma once

#include <vector>

#include <fink/core/symbol.hpp>
#include <fink/core/timestamp.hpp>
#include <fink/market/book_level.hpp>

namespace fink::market {

struct BookSnapshot {
    fink::core::Symbol symbol;
    fink::core::Timestamp timestamp;

    std::vector<BookLevel> bids;
    std::vector<BookLevel> asks;
};

} // namespace fink::market