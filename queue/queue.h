#include <array>
#include <atomic>
#include <cstdint>

namespace LockFree {

template <typename T> struct Elem {
  T real_elem_{};
  bool empty_ = 0;
};

template <typename T> class Queue {
public:
  static constexpr uint64_t MAX_QUEUE_SIZE = 1024;
  Queue() : elems_(), back_(0) {}
  ~Queue() = default;
  void enque(const T &elem);
  T deque();

private:
  std::array<std::atomic<Elem<T>>, MAX_QUEUE_SIZE> elems_;
  std::atomic_uint64_t back_;
};

template <typename T> void Queue<T>::enque(const T &elem) {
  uint64_t idx = back_.fetch_add(1);
  elems_[idx].store(Elem<T>{elem, false}, std::memory_order_relaxed);
}

template <typename T> T Queue<T>::deque() {
  uint64_t back_idx = back_.load(std::memory_order_relaxed);
  for (int i = 0; i < 100; i++) {
    for (uint64_t i = 0; i < back_idx; i++) {
      Elem<T> idx_elem =
          elems_[i].exchange(Elem<T>{T{}, true}, std::memory_order_relaxed);
      if (!idx_elem.empty_)
        return idx_elem.real_elem_;
    }
  }
  return T{};
}
} // namespace LockFree