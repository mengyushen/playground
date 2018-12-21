#include <boost/locale.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace boost;

int main() {
  boost::locale::generator gen;
  std::locale::global(gen(""));
  string name = "無尾熊";
  cout << locale::to_lower(name) << endl;
}
