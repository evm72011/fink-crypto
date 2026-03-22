#include <gtest/gtest.h>

#include <fink/core/price.hpp>
#include <fink/core/quantity.hpp>
#include <fink/core/symbol.hpp>
#include <fink/core/timestamp.hpp>
#include <fink/market/book_level.hpp>
#include <fink/market/book_snapshot.hpp>
#include <fink/market/book_update.hpp>
#include <fink/orderbook/apply_error.hpp>
#include <fink/orderbook/order_book.hpp>

namespace {

using fink::core::Price;
using fink::core::Quantity;
using fink::core::Symbol;
using fink::core::Timestamp;
using fink::market::BookLevel;
using fink::market::BookSnapshot;
using fink::market::BookUpdate;
using fink::orderbook::ApplyError;
using fink::orderbook::OrderBook;

TEST(OrderBookTests, AppliesSnapshotAndCalculatesTopSpreadAndMidPrice) {
  OrderBook book{Symbol{"BTCUSDT"}};

  BookSnapshot snapshot{
      .symbol = Symbol{"BTCUSDT"},
      .timestamp = Timestamp{1},
      .bids = {BookLevel{.price = Price{100.0}, .quantity = Quantity{2.0}},
               BookLevel{.price = Price{99.0}, .quantity = Quantity{3.0}}},
      .asks = {BookLevel{.price = Price{101.0}, .quantity = Quantity{1.5}},
               BookLevel{.price = Price{102.0}, .quantity = Quantity{4.0}}}};

  const auto result = book.apply(snapshot);
  ASSERT_TRUE(result.has_value());

  const auto bestBid = book.best_bid();
  ASSERT_TRUE(bestBid.has_value());
  EXPECT_DOUBLE_EQ(bestBid->price.value(), 100.0);
  EXPECT_DOUBLE_EQ(bestBid->quantity.value(), 2.0);

  const auto bestAsk = book.best_ask();
  ASSERT_TRUE(bestAsk.has_value());
  EXPECT_DOUBLE_EQ(bestAsk->price.value(), 101.0);
  EXPECT_DOUBLE_EQ(bestAsk->quantity.value(), 1.5);

  const auto spread = book.spread();
  ASSERT_TRUE(spread.has_value());
  EXPECT_DOUBLE_EQ(*spread, 1.0);

  const auto midPrice = book.mid_price();
  ASSERT_TRUE(midPrice.has_value());
  EXPECT_DOUBLE_EQ(*midPrice, 100.5);
}

TEST(OrderBookTests, AppliesIncrementalUpdateAndRemovesLevelWithZeroQuantity) {
  OrderBook book{Symbol{"BTCUSDT"}};

  BookSnapshot snapshot{
      .symbol = Symbol{"BTCUSDT"},
      .timestamp = Timestamp{1},
      .bids = {BookLevel{.price = Price{100.0}, .quantity = Quantity{2.0}}},
      .asks = {BookLevel{.price = Price{101.0}, .quantity = Quantity{1.0}}}};

  ASSERT_TRUE(book.apply(snapshot).has_value());

  BookUpdate update{
      .symbol = Symbol{"BTCUSDT"},
      .timestamp = Timestamp{2},
      .bids = {BookLevel{.price = Price{100.0}, .quantity = Quantity{0.0}},
               BookLevel{.price = Price{100.5}, .quantity = Quantity{1.25}}},
      .asks = {}};

  const auto result = book.apply(update);
  ASSERT_TRUE(result.has_value());

  const auto bestBid = book.best_bid();
  ASSERT_TRUE(bestBid.has_value());
  EXPECT_DOUBLE_EQ(bestBid->price.value(), 100.5);
  EXPECT_DOUBLE_EQ(bestBid->quantity.value(), 1.25);
}

TEST(OrderBookTests, ReturnsSymbolMismatchForSnapshotWithDifferentSymbol) {
  OrderBook book{Symbol{"BTCUSDT"}};

  BookSnapshot snapshot{.symbol = Symbol{"ETHUSDT"},
                        .timestamp = Timestamp{1},
                        .bids = {},
                        .asks = {}};

  const auto result = book.apply(snapshot);

  ASSERT_FALSE(result.has_value());
  EXPECT_EQ(result.error(), ApplyError::SymbolMismatch);
}

TEST(OrderBookTests, EmptyOrderBookAcceptsFirstSnapshotAndSetsSymbol) {
  OrderBook book;

  BookSnapshot snapshot{
      .symbol = Symbol{"BTCUSDT"},
      .timestamp = Timestamp{1},
      .bids = {BookLevel{.price = Price{100.0}, .quantity = Quantity{2.0}}},
      .asks = {BookLevel{.price = Price{101.0}, .quantity = Quantity{1.0}}}};

  const auto result = book.apply(snapshot);

  ASSERT_TRUE(result.has_value());
  EXPECT_EQ(book.symbol().value(), "BTCUSDT");
}

TEST(OrderBookTests, ReturnsEmptyOptionalsWhenBookHasNoTopLevels) {
  OrderBook book{Symbol{"BTCUSDT"}};

  EXPECT_FALSE(book.best_bid().has_value());
  EXPECT_FALSE(book.best_ask().has_value());
  EXPECT_FALSE(book.spread().has_value());
  EXPECT_FALSE(book.mid_price().has_value());
}

} // namespace