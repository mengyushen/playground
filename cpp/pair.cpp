
#include <algorithm>
#include <iostream>
#include <utility>

using namespace std;
int main() {
  vector<pair<int, int>> vec;
  for (int i = 0; i < 3; ++i) {
    for (int j = 6; j > 4; j--) {
      vec.emplace_back(make_pair(j, i));
    }
  }

  for (auto v : vec) {
    cout << "[" << v.first << ", " << v.second << "]" << endl;
  }
  cout << "================================" << endl;
  std::sort(vec.begin(), vec.end(),
            [](pair<int, int> &left, pair<int, int> &right) {
              if (left.first == right.first) {
                return left.second > right.second;
              }
              return left.first < right.first;
            });
  for (auto v : vec) {
    cout << "[" << v.first << ", " << v.second << "]" << endl;
  }
}
