#include "serial_linear.h"

#include "serial_linear.h"
void serial_linear(ofstream& out, int n, vector<elem_t> v, bool print, int d, int _) {
  elem_t sum = d == 0 ? (elem_t) 0 : (elem_t) vector<float>(d, 0.0);
  for (int i = 0; i < n; i++) {
    sum += v[i];
    if (print) out << to_string(sum) << " ";
  }
}