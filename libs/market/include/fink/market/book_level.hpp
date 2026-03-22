#pragma once

#include <fink/core/price.hpp>
#include <fink/core/quantity.hpp>

namespace fink::market {

struct BookLevel {
  fink::core::Price price;
  fink::core::Quantity quantity;
};

} // namespace fink::market