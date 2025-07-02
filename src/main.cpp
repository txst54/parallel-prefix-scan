#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>

#include "sequential/serial_linear.h"
#include "sequential/seq_tree.h"
#include "parallel/p_tree.h"
#include "parallel/p_block.h"
#include "inc.h"

using namespace std;

void execute(void f(ofstream&, int, vector<elem_t>, bool, int, int), ofstream& out,
             const int n, const vector<elem_t>& v, const string& p_name, int num_iters, bool print, int d, int num_threads) {
  if (print) out << "<" << p_name << ">: ";
  f(out, n, v, print, d, num_threads);
  float avg_duration = 0;
  for (int i = 0; i < num_iters; i++) {
    auto start = chrono::high_resolution_clock::now();
    f(out, n, v, false, d, num_threads);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    avg_duration += static_cast<float>(duration.count());
  }
  avg_duration /= static_cast<float>(num_iters);
  string prefix = print ? "\n" : "";
  out << prefix << "<" << p_name << ">: execution took " << avg_duration << " microseconds\n";
}

int main() {
  ifstream in("test.in");
  ofstream out("test.out");
  int d, n;
  in >> d >> n;
  vector<elem_t> v(n);
  if (d == 0) {
    for (int i = 0; i < n; i++) {
      int k;
      in >> k;
      v[i] = k;
    }
  } else {
    for (int i = 0; i < n; i++) {
      vector<float> vec(d);
      for (int j = 0; j < d; j++) {
        in >> vec[j];
      }
      v[i] = vec;
    }
  }
  execute(serial_linear, out, n, v, "serial_linear", NUM_ITERS, PRINT, d, 0);
  execute(seq_tree, out, n, v, "seq_tree", NUM_ITERS, PRINT, d, 0);

  for (int i = 2; i <= 32; i += 2) {
    string to_append = " {threads: " + to_string(i) + "}";
    execute(p_tree, out, n, v, "p_tree" + to_append, NUM_ITERS, PRINT, d, i);
    execute(p_block, out, n, v, "p_block" + to_append, NUM_ITERS, PRINT, d, i);
  }
  return 0;
}
