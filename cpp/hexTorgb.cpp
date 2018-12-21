#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

string HexToRGBA(string hex, float opacity) {
  int *rgb = new int[3];
  stringstream ss, res;
  string str;

  for (int i = 0; i < 3; ++i) {
    str = hex.substr(i * 2, 2);
    ss << std::hex << str;
    ss >> rgb[i];
    ss.clear();
  }
  opacity = opacity / 100;
  res.precision(2);
  res << "rgba(" << rgb[0] << "," << rgb[1] << "," << rgb[2] << ","
      << std::fixed << opacity << ")";
  return res.str();
}

int main(int argc, char **argv) {
  //	cout << HexToRGBA(argv[1], (float)atoi(argv[2])) << endl;
  char back[255];
  string a();
  sprintf(a.c_str(), "background, %.2f", (float)123 / 1000);
  cout << back;
  return 0;
}
