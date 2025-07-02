#include <vector>
#include <fstream>
#include "../inc.h"
using namespace std;

#ifndef PARALLEL_PREFIX_SUMS_P_TREE_H
#define PARALLEL_PREFIX_SUMS_P_TREE_H


typedef struct PTreeThreadArgs {
  vector<elem_t>* v;
  int n;
  int tid;
  int p;
  pthread_barrier_t* barrier;
} p_tree_thread_args_t;

void p_tree(ofstream& out, int n, vector<elem_t> v, bool print, int d, int num_threads);

#endif //PARALLEL_PREFIX_SUMS_P_TREE_H
