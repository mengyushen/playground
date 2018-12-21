#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>

using namespace std;

const string kDataVersionConfigPath =
    "/package-6.0/source/synophoto/etc/data_version";

int getNewstDBVersion() {
  int version = 0;
  cout << kDataVersionConfigPath << endl;
  std::ifstream config(kDataVersionConfigPath.c_str());

  std::string line;
  while (std::getline(config, line)) {
    cout << line << endl;
    std::istringstream is_line(line);
    std::string key;
    if (std::getline(is_line, key, '=')) {
      cout << key << endl;
      std::string value;
      if (std::getline(is_line, value)) {
        cout << value << endl;
        version = atoi(value.c_str());
      }
    }
  }
  return version;
}

int main() {
  cout << getNewstDBVersion() << endl;
  return 0;
}
// extract to string
//#include <iostream>
//#include <fstream>
//#include <string>
//
// const std::string kDataVersionConfigPath =
// "/package-6.0/source/synophoto/etc/data_version";
//
// int main ()
//{
//  std::string name;
//  std::ifstream ifs (kDataVersionConfigPath.c_str());
//  char c = ifs.get();
//  while (ifs.good()) {
//    std::cout << c;
//    c = ifs.get();
//  }
//  ifs.close();
//
//  return 0;
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
