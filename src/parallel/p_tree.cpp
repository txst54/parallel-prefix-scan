#include "p_tree.h"

void* parallel_scan_worker(void* arg) {
  auto* args = (p_tree_thread_args_t*)arg;
  vector<elem_t>& v = *(args->v);
  int n = args->n;
  int tid = args->tid;
  int p = args->p;
  pthread_barrier_t* barrier = args->barrier;

  for (int i = 2; i <= n; i *= 2) {
    // j is the current group start
    int num_groups = (n + i - 1) / i; // ceil of n / i
    int work_per_thread = (num_groups + p - 1) / p; // ceil of num_groups / p
    int start = tid * work_per_thread;
    int end = min(num_groups, (tid + 1) * work_per_thread);
    for (int g = start; g < end; g++) {
      int j = g * i;
      int group_end = j + i - 1; // sum the second half
      int group_start = j + i / 2 - 1; // sum the first half
      if (group_end < n) {
        v[group_end] = v[group_start] + v[group_end];
      }
    }
    pthread_barrier_wait(barrier);
  }
  for (int i = n / 2;i >= 2; i/=2) {
    int num_groups = (n + i - 1) / i; // ceil of n / i
    int work_per_thread = (num_groups + p - 1) / p; // ceil of num_groups / p
    int start = tid * work_per_thread;
    int end = min(num_groups, (tid + 1) * work_per_thread);
    // start at an offset
    for (int g = start; g < end; g++) {
      int j = g * i + i - 1;
      int group_end = j + i / 2;
      int group_start = j;
      if (group_end < n) {
        v[group_end] = v[group_start]+v[group_end];
      }
    }
    pthread_barrier_wait(barrier);
  }
  return nullptr;
}

void p_tree(ofstream& out, int n, vector<elem_t> v, bool print, int d, int num_threads) {
  pthread_barrier_t barrier;
  pthread_barrier_init(&barrier, nullptr, num_threads);
  vector<pthread_t> threads(num_threads);
  vector<p_tree_thread_args_t> args(num_threads);

  for (int i = 0; i < num_threads; i++) {
    args[i] = p_tree_thread_args_t{&v, n, i, num_threads, &barrier};
    pthread_create(&threads[i], nullptr, parallel_scan_worker, &args[i]);
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