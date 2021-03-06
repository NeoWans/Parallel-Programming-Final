#include <bits/stdc++.h>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>

#include "bitset_matrix.hh"
#include "constant.hh"
using namespace std;
namespace fs = filesystem;

const auto          num_thread = thread::hardware_concurrency();
boost::shared_mutex mutex_main;

void thread_callback(size_t index, bitset_matrix_t& m) {
  for (size_t local_index = index; local_index < m.op.size();
       local_index += num_thread) {
    auto& eliminatee = m.op.at(local_index);
    while (eliminatee.any()) {
      auto key = bsmap(eliminatee._Find_first());
      boost::upgrade_lock<boost::shared_mutex> read_lock(mutex_main);
      auto&                                    eliminater = m.pool[key];
      if (eliminater.none()) {
        boost::upgrade_to_unique_lock<boost::shared_mutex> write_lock(
          read_lock);
        eliminater = eliminatee;
        break;
      } else eliminatee ^= eliminater;
    }
  }
}

void gauss(bitset_matrix_t& m) {
  list<thread> thread_pool;
  for (unsigned i = 0; i < num_thread; ++i)
    thread_pool.push_back(thread(thread_callback, i, ref(m)));
  for (auto& t : thread_pool) t.join();
}

// 必须接受至少一个参数，第一个参数指向输入目录，内容为 i.0 i.1 i.2，表示 i
// 组数据的非零消元子 被消元行
// 样例消元结果。第二可选参数指向输出目录，如果存在则向目录内写入 i.out
// 文件，代表程序的消元结果。程序会向标准输出打印每组测试样例的用时。
signed main(int argc, char* argv[]) {
  if (argc < 2) exit(EXIT_FAILURE);
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  for (size_t i = 1; i <= cases; ++i) {
    bitset_matrix_t m;
    m.read(argv[1], i);
    auto t1 = chrono::high_resolution_clock::now();
    gauss(m);
    auto t2 = chrono::high_resolution_clock::now();
    auto chrono_time =
      chrono::duration_cast<chrono::duration<double, std::milli>>(t2 - t1);
    cout.precision(9);
    cout << "N: " << matrix_sz[i] << " time: " << chrono_time.count() << " ms"
         << endl;
    if (argc >= 3) {
      fs::path      out_dir(argv[2]);
      ostringstream oss;
      oss << i;
      auto     out_file = out_dir / (oss.str() + ".out");
      ofstream ofs;
      ofs.open(out_file);
      auto cout_orig = cout.rdbuf(ofs.rdbuf());
      for (const auto& line : m.op) {
        for (auto idx = line._Find_first(), pos = bsmap(idx); idx < line.size();
             idx = line._Find_next(idx), pos = bsmap(idx))
          cout << pos << " ";
        cout << '\n';
      }
      cout.rdbuf(cout_orig);
      ofs.close();
    }
  }
}