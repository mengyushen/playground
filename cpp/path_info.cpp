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
             << "filename: " << path.filename().string() << std::endl
             << "relative_path: " << path.relative_path().string() << std::endl
             << "parent_path: " << path.parent_path().string() << std::endl
             << "extension: " << path.extension().string() << std::endl;
  
  return 0;
}
