#include <variant>
#include <sstream>
#include <vector>
using namespace std;

#ifndef PARALLEL_PREFIX_SUMS_INC_H
#define PARALLEL_PREFIX_SUMS_INC_H
#define NUM_THREADS 24
#define NUM_ITERS 10
#define PRINT true

typedef variant<int, vector<float>> elem_t;
elem_t operator+(const elem_t& a, const elem_t& b);
elem_t& operator+=(elem_t& a, const elem_t& b);

inline std::string to_string(const elem_t& e) {
  struct {
    std::string operator()(int val) const {
      return std::to_string(val);
    }

    std::string operator()(const vector<float>& vec) const {
      std::ostringstream oss;
      oss << "[";
      for (size_t i = 0; i < vec.size(); ++i) {
        oss << vec[i];
        if (i + 1 < vec.size()) oss << ", ";
      }
      oss << "]";
      return oss.str();
    }
  } visitor;

  return std::visit(visitor, e);
}

#endif //PARALLEL_PREFIX_SUMS_INC_H
