#include <vector>
#include <fstream>
#include "../inc.h"

using namespace std;

#ifndef PARALLEL_PREFIX_SUMS_P_BLOCK_H
#define PARALLEL_PREFIX_SUMS_P_BLOCK_H

typedef struct PBlockThreadArgs {
  vector<elem_t>* v;
  vector<elem_t>* block_sum;
  vector<elem_t>* block_offset;
  elem_t* init_val;
  bool* global_sense;
  int* arrived;
  int n;
  int tid;
  int p;
  pthread_barrier_t* barrier;
} p_block_thread_args_t;

void p_block(ofstream& out, int n, vector<elem_t> v, bool print, int d, int num_threads);

#endif //PARALLEL_PREFIX_SUMS_P_BLOCK_H
