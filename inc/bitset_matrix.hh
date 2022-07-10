#pragma once
#include <bits/stdc++.h>

#include "constant.hh"

#define bsmap(i) (matrix_max_sz - 1 - (i))
class bitset_matrix_t {
public:
  using bitset_t = std::bitset<matrix_max_sz>;
  void read(const char* dir, int test_case);

  size_t                     row_sz;
  std::map<size_t, bitset_t> pool;
  std::vector<bitset_t>      op;
};