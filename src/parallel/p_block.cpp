#include <iostream>
#include <thread>
#include "p_block.h"

void sense_reversing_barrier(bool& global_sense, bool& local_sense, int& arrived, int p) {
  local_sense = !local_sense;

  int position = __sync_fetch_and_add(&arrived, 1);

  if (position == p - 1) {
    arrived = 0;
    global_sense = local_sense;
  } else {
    while (global_sense != local_sense) {
      this_thread::yield();
    }
  }
}

void* parallel_scan_worker_1(void* arg) {
  auto* args = (p_block_thread_args_t *)arg;
  bool local_sense = true;
  vector<elem_t>& v = *(args->v);
  vector<elem_t>& block_sum = *(args->block_sum);
  vector<elem_t>& block_offset = *(args->block_offset);
  elem_t& init_val = *(args->init_val);
  bool& global_sense = *(args->global_sense);
  int& arrived = *(args->arrived);
  int n = args->n;
  int tid = args->tid;
  int p = args->p;
  pthread_barrier_t* barrier = args->barrier;

  int group_size = (n + p - 1) / p;
  int start = tid * group_size;
  int end = min(start + group_size, n);
  block_sum[tid] = 0;
  if (start < end) {
    for (int j = start + 1; j < end; j++) {
      v[j] = v[j - 1] + v[j];
    }
    block_sum[tid] = v[end - 1];
  }
  // pthread_barrier_wait(barrier);
  sense_reversing_barrier(global_sense, local_sense, arrived, p);
  if (tid == 0) {
    block_offset[0] = init_val;
    for (int i = 1; i < p; i++) {
      block_offset[i] = block_offset[i - 1] + block_sum[i - 1];
    }
  }
  // pthread_barrier_wait(barrier);
  sense_reversing_barrier(global_sense, local_sense, arrived, p);
  if (start < end) {
    elem_t offset = block_offset[tid];
    for (int i = start; i < end; ++i) {
      v[i] += offset;
    }
  }
  return nullptr;
}


void p_block(ofstream& out, int n, vector<elem_t> v, bool print, int d, int num_threads) {
  bool global_sense = true;
  int arrived = 0;

  elem_t init_val = d == 0 ? (elem_t) 0 : (elem_t) vector<float>(d, 0.0);
  pthread_barrier_t barrier;
  pthread_barrier_init(&barrier, nullptr, num_threads);
  vector<pthread_t> threads(num_threads);
  vector<p_block_thread_args_t> args(num_threads);
  vector<elem_t> block_sum(num_threads, init_val);
  vector<elem_t> block_offset(num_threads, init_val);

  for (int i = 0; i < num_threads; i++) {
    args[i] = p_block_thread_args_t{&v, &block_sum, &block_offset, &init_val, &global_sense, &arrived, n, i, num_threads, &barrier};
    pthread_create(&threads[i], nullptr, parallel_scan_worker_1, &args[i]);
  }

  for (int i = 0; i < num_threads; i++) {
    pthread_join(threads[i], nullptr);
  }

  pthread_barrier_destroy(&barrier);

  if (print) {
    for (int k = 0; k < n; k++) {
      out << to_string(v[k]) << " ";
    }
  }
}