#include <utility>
#include <boost/filesystem.hpp>
#include <iostream>
#include <string>
#include <boost/algorithm/string/classification.hpp>

namespace fs = boost::filesystem;

int main (int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << argv[0] << " path" << std::endl;
    return 0;
  }
  fs::path path{argv[1]};
  std:: cout << path.string() << std::endl
             << path.extension().string() << std::endl;
  
  return 0;
}
