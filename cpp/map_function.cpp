
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

using namespace std;

void a() { cout << "a\n"; }

void b() { cout << "b\n"; }

const std::unordered_map<int32_t, std::function<void()>> imap = {
    {2, b}, {3, a},
};

int main(int argc, char **argv) {
  int version = std::atoi(argv[1]);
  for (int i = 1; i <= version; ++i) {
    cout << "i: " << i << endl;
    auto it = imap.find(i);
    if (it != imap.end()) {
      cout << it->first << endl;
      it->second();
    }
  }
  return 0;
}
