
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>

int main(int c, char **argv) {
  using std::string;
  using std::cout;

  struct tm tm;
  string input_time = string(argv[1]);

  string DATE_FORMAT = "%Y:%m:%d %H:%M:%S";
  cout << "input " << input_time << std::endl;
  // workaround for avoid 0000 year. TODO: method for recognizing big, little
  // month (ex: 4m31d is a wrong date)
  if (NULL != strptime(input_time.c_str(), DATE_FORMAT.c_str(), &tm)) {
    cout << "year: " << tm.tm_year;
    cout << std::endl;
    cout << "month: " << tm.tm_mon;
    cout << std::endl;
    cout << "day: " << tm.tm_mday;
    cout << std::endl;
  } else {
    cout << "parse error" << std::endl;
  }
  int timearg[6] = {0};
  if (6 == sscanf(input_time.c_str(), "%d:%d:%d %d:%d:%d", &timearg[0],
                  &timearg[1], &timearg[2], &timearg[3], &timearg[4],
                  &timearg[5])) {
    printf("%04d-%02d-%02d %02d:%02d:%02d\n", timearg[0], timearg[1],
           timearg[2], timearg[3], timearg[4], timearg[5]);
  }
  return 0;
}
