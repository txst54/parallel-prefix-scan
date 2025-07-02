#include <fstream>
#include <vector>
#include "../inc.h"
using namespace std;

#ifndef PARALLEL_PREFIX_SUMS_SERIAL_LINEAR_H
#define PARALLEL_PREFIX_SUMS_SERIAL_LINEAR_H
void serial_linear(ofstream& out, int n, vector<elem_t> v, bool print, int d, int _);


#endif //PARALLEL_PREFIX_SUMS_SERIAL_LINEAR_H
