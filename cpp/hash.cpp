#include <fstream>
#include <iostream>
#include <string>

#include <boost/algorithm/hex.hpp>
#include <openssl/md5.h>

int FileStartOffset = 100 * 1024;
int Size = 200 * 1024;
int MinSize = 300 * 1024;

using namespace std;
string calculate(string &buffer);

char buffer[200 * 1024 + 1] = {0};
int blockSize = Size;

string FileHash(string &path) {
  ifstream file(path, ios::in | ios::binary | ios::ate);
  int start;
  if (file.is_open()) {
    int length = file.tellg();
    if (length < MinSize) {
      start = 0;
      blockSize = length;
    } else {
      start = FileStartOffset;
      blockSize = Size;
    }
    file.seekg(start, file.beg);
    file.read(buffer, blockSize);
    file.close();
  }
  string out(buffer, blockSize);

  return out;
}

string calculate(string &data) {
  unsigned char result[32] = {0};
  MD5((const unsigned char *)data.c_str(), data.length(), result);

  return boost::algorithm::hex(string((const char *)result));
}

int main(int argc, char *argv[]) {
  string filename(argv[1]);
  string data = FileHash(filename);
  string output = calculate(data);
  cout << output << endl;
}
