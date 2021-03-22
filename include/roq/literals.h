/* Copyright (c) 2017-2021, Hans Erik Thrane */

#pragma once

// objectives:
// - type-safe format strings
// - avoid 'char const *' use cases implying the run-time use of strlen

#include <string>
#include <string_view>

#include "roq/format_str.h"

namespace roq {
inline namespace literals {
inline std::string operator"" _s(char const *str, size_t len) {
  using namespace std::literals;
  return std::literals::string_literals::operator"" s(str, len);
}

inline constexpr std::string_view operator"" _sv(char const *str, size_t len) {
  using namespace std::literals;
  return std::literals::string_view_literals::operator"" sv(str, len);
}

// TODO(thraneh): wrap std::string_view and coordinate with roq-logging
inline constexpr format_str operator"" _fmt(char const *str, size_t len) {
  using namespace std::literals;
  return format_str(std::literals::string_view_literals::operator"" sv(str, len));
}
}  // namespace literals
}  // namespace roq