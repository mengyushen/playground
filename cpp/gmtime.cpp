#include <time.h>
#include <iostream>
#include <string>

using namespace std;

void print_time(int64_t date)
{
  char year[10], month[10], day[10];
  const time_t timestamp = static_cast<time_t>(date);
  struct tm datetime;
  gmtime_r(&timestamp, &datetime);
  strftime(year, sizeof(year), "%Y", &datetime);
  strftime(month, sizeof(month), "%m", &datetime);
  strftime(day, sizeof(day), "%d", &datetime);

  cout << "year: " << year << endl;
  cout << "month: " << month << endl;
  cout << "day: " << day << endl;
}

void usage(char* name)
{
  cerr << "Usage: " << name << " unixtimestamp"<< std::endl;
  cerr << std::endl;
}

int main(int argc, char* argv[])
{
  if (argc < 2) {
    usage(argv[0]);
    return -1;
  }
  int64_t date = strtoll(argv[1], nullptr, 10);
  print_time(date);
  return 0;
}
