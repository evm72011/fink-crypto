#include <utility>

#include <fink/core/price.hpp>
#include <fink/orderbook/order_book.hpp>

namespace fink::orderbook {

OrderBook::OrderBook(fink::core::Symbol symbol)
    : symbol_(std::move(symbol)), bids_(), asks_() {}

std::expected<void, ApplyError>
OrderBook::apply(const fink::market::BookSnapshot &snapshot) {
  if (!symbol_is_compatible(snapshot.symbol)) {
    return std::unexpected(ApplyError::SymbolMismatch);
  }

  symbol_ = snapshot.symbol;
  clear();

  for (const auto &level : snapshot.bids) {
    apply_bid_level(level);
  }

  for (const auto &level : snapshot.asks) {
    apply_ask_level(level);
  }

  return {};
}

std::expected<void, ApplyError>
OrderBook::apply(const fink::market::BookUpdate &update) {
  if (!symbol_is_compatible(update.symbol)) {
    return std::unexpected(ApplyError::SymbolMismatch);
  }

  symbol_ = update.symbol;

  for (const auto &level : update.bids) {
    apply_bid_level(level);
  }

  for (const auto &level : update.asks) {
    apply_ask_level(level);
  }

  return {};
}

const fink::core::Symbol &OrderBook::symbol() const noexcept { return symbol_; }

bool OrderBook::empty() const noexcept {
  return bids_.empty() && asks_.empty();
}

bool OrderBook::has_bids() const noexcept { return !bids_.empty(); }

bool OrderBook::has_asks() const noexcept { return !asks_.empty(); }

std::optional<BookTopLevel> OrderBook::best_bid() const noexcept {
  if (bids_.empty()) {
    return std::nullopt;
  }

  const auto &[price, quantity] = *bids_.begin();

  return BookTopLevel{.price = fink::core::Price{price}, .quantity = quantity};
}

std::optional<BookTopLevel> OrderBook::best_ask() const noexcept {
  if (asks_.empty()) {
    return std::nullopt;
  }

  const auto &[price, quantity] = *asks_.begin();

  return BookTopLevel{.price = fink::core::Price{price}, .quantity = quantity};
}

BookTop OrderBook::top() const noexcept {
  return BookTop{.best_bid = best_bid(), .best_ask = best_ask()};
}

std::optional<double> OrderBook::spread() const noexcept {
  const auto bid = best_bid();
  const auto ask = best_ask();

  if (!bid.has_value() || !ask.has_value()) {
    return std::nullopt;
  }

  return ask->price.value() - bid->price.value();
}

std::optional<double> OrderBook::mid_price() const noexcept {
  const auto bid = best_bid();
  const auto ask = best_ask();

  if (!bid.has_value() || !ask.has_value()) {
    return std::nullopt;
  }

  return (bid->price.value() + ask->price.value()) / 2.0;
}

void OrderBook::apply_bid_level(const fink::market::BookLevel &level) {
  const auto price = level.price.value();
  const auto quantity = level.quantity.value();

  if (quantity == 0.0) {
    bids_.erase(price);
    return;
  }

  bids_[price] = level.quantity;
}

void OrderBook::apply_ask_level(const fink::market::BookLevel &level) {
  const auto price = level.price.value();
  const auto quantity = level.quantity.value();

  if (quantity == 0.0) {
    asks_.erase(price);
    return;
  }

  asks_[price] = level.quantity;
}

void OrderBook::clear() noexcept {
  bids_.clear();
  asks_.clear();
}

bool OrderBook::symbol_is_compatible(
    const fink::core::Symbol &symbol) const noexcept {
  return symbol_.value().empty() || symbol_.value() == symbol.value();
}

} // namespace fink::orderbook
