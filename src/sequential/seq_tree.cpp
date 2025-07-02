#include "seq_tree.h"

void seq_tree(ofstream& out, int n, vector<elem_t> v, bool print, int d, int _) {
  // i is the step
  int START = 2;
  int i = START;
  for (;i <= n; i *= 2) {
    // j is the current group start
    for (int j = 0; j < n; j += i) {
      int group_end = j + i - 1; // sum the second half
      int group_start = j + i / 2 - 1; // sum the first half
      if (group_end < n) {
        v[group_end] = v[group_start] + v[group_end];
      }
    }
  }
  for (;i >= START; i/=2) {
    // start at an offset
    for (int j = i - 1; j < n; j += i) {
      int group_end = j + i / 2;
      int group_start = j;
      if (group_end < n) {
        v[group_end] = v[group_start]+v[group_end];
      }
    }
  }
  if (print) {
    for (int k = 0; k < n; k++) {
      out << to_string(v[k]) << " ";
    }
  }
}