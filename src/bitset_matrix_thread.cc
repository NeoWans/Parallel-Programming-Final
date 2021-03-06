#include <bits/stdc++.h>

#include "bitset_matrix_thread.hh"
using namespace std;
namespace fs = filesystem;

void bitset_matrix_t::read(const char* dir, int test_case) {
  row_sz = matrix_sz[test_case];
  ostringstream oss;
  fs::path      res_dir(dir);
  oss << test_case;
  auto     pool_file = res_dir / (oss.str() + ".0");
  ifstream ifs;
  ifs.open(pool_file);
  cin.rdbuf(ifs.rdbuf());
  string line;
  while (getline(cin, line)) {
    istringstream iss(line);
    size_t        key, val;
    iss >> key;
    call_once(flag_v[key], []() -> void {});
    auto& row = pool[key];
    row.set(bsmap(key));
    while (iss >> val) row.set(bsmap(val));
  }
  ifs.close();
  auto op_file = res_dir / (oss.str() + ".1");
  ifs.open(op_file);
  cin.rdbuf(ifs.rdbuf());
  op_sz = 0;
  while (getline(cin, line)) {
    istringstream iss(line);
    size_t        val;
    bitset_t      row;
    while (iss >> val) row.set(bsmap(val));
    op[op_sz++] = move(row);
  }
  ifs.close();
}
