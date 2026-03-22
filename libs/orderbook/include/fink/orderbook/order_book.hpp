#pragma once

#include <expected>
#include <functional>
#include <map>
#include <optional>

#include <fink/core/symbol.hpp>
#include <fink/core/quantity.hpp>
#include <fink/market/book_level.hpp>
#include <fink/market/book_snapshot.hpp>
#include <fink/market/book_update.hpp>
#include <fink/orderbook/apply_error.hpp>
#include <fink/orderbook/book_top.hpp>

namespace fink::orderbook {

class OrderBook {
public:
    OrderBook() : symbol_(), bids_(), asks_() { }
    explicit OrderBook(fink::core::Symbol symbol);

    [[nodiscard]] std::expected<void, ApplyError> apply(const fink::market::BookSnapshot& snapshot);
    [[nodiscard]] std::expected<void, ApplyError> apply(const fink::market::BookUpdate& update);

    [[nodiscard]] const fink::core::Symbol& symbol() const noexcept;

    [[nodiscard]] bool empty() const noexcept;
    [[nodiscard]] bool has_bids() const noexcept;
    [[nodiscard]] bool has_asks() const noexcept;

    [[nodiscard]] std::optional<BookTopLevel> best_bid() const noexcept;
    [[nodiscard]] std::optional<BookTopLevel> best_ask() const noexcept;
    [[nodiscard]] BookTop top() const noexcept;

    [[nodiscard]] std::optional<double> spread() const noexcept;
    [[nodiscard]] std::optional<double> mid_price() const noexcept;

private:
    using BidLevels = std::map<double, fink::core::Quantity, std::greater<>>;
    using AskLevels = std::map<double, fink::core::Quantity, std::less<>>;

    void apply_bid_level(const fink::market::BookLevel& level);
    void apply_ask_level(const fink::market::BookLevel& level);
    void clear() noexcept;

    [[nodiscard]] bool symbol_is_compatible(const fink::core::Symbol& symbol) const noexcept;

private:
    fink::core::Symbol symbol_;
    BidLevels bids_;
    AskLevels asks_;
};

} // namespace fink::orderbook