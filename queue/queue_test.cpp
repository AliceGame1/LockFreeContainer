#include "queue.h"
#include <iostream>
#include <thread>

using namespace std;

static void enq_n_times(LockFree::Queue<int> &que, uint32_t time) {
  for (uint32_t i = 0; i < time; i++) {
    que.enque(i);
  }
}

static void deq_n_times(LockFree::Queue<int> &que, uint32_t time) {
  for (uint32_t i = 0; i < time; i++) {
    int num = que.deque();
    if (num != i)
      cerr << "there are error in queue " << i << "|" << num << endl;
  }
}

int main() {
  LockFree::Queue<int> que;
  std::thread thd_a(&enq_n_times, std::ref(que), 1000);
  std::this_thread::sleep_for(100ms);
  std::thread thd_b(&deq_n_times, std::ref(que), 1000);

  thd_a.join();
  thd_b.join();

  return 0;
}