#include <exception>
#include <iostream>

int main() {
  try {
    try {
      throw std::runtime_error("123");
    } catch (...) {
      throw;
    }
  } catch (const std::runtime_error &e) {
    std::cout << "runttime error " << e.what();
  } catch (const std::exception &e) {
    std::cout << "exception " << e.what();
  }
  std::cout << std::endl;
  return 0;
}
