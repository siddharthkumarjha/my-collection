#include <future>
#include <iostream>
#include <thread>

std::future<void> callfn(void) {
  auto lambda = []() -> void {
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(35ms);
    std::cout << "35ms passed" << '\n';
  };
  return std::async(std::launch::async, lambda);
}

int main(void) {
  std::cout << "before async" << '\n';
  std::future<void> fut = callfn();
  std::cout << "after async" << '\n';
  return 0;
}
