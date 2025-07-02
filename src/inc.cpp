#include "inc.h"

elem_t operator+(const elem_t& a, const elem_t& b) {
  return std::visit([](const auto& lhs, const auto& rhs) -> elem_t {
    using L = std::decay_t<decltype(lhs)>;
    using R = std::decay_t<decltype(rhs)>;

    if constexpr (std::is_same_v<L, int> && std::is_same_v<R, int>) {
      return lhs + rhs;
    } else if constexpr (std::is_same_v<L, std::vector<float>> && std::is_same_v<R, std::vector<float>>) {
      std::vector<float> result(std::max(lhs.size(), rhs.size()), 0.0f);
      for (size_t i = 0; i < lhs.size(); ++i) result[i] += lhs[i];
      for (size_t i = 0; i < rhs.size(); ++i) result[i] += rhs[i];
      return result;
    } else {
      throw std::runtime_error("Unsupported variant combination");
    }
  }, a, b);
}

elem_t& operator+=(elem_t& a, const elem_t& b) {
  a = a + b;  // Reuse your existing operator+
  return a;
}