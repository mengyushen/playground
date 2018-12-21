#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <functional>
#include <ctime>
#include <iostream>
#include <regex>
#include <set>
#include <string>

using namespace std;
string CorrectTimeFormat(const string& date_time)
{
  // If time format is broken, fill it with 0.
  // Example:
  //   1. empty, ":", "::"    => 00:00:00
  //   2. "12", "12:", "12::" => 12:00:00
  //   3. "12:30", "12:30:"   => 12:30:00
  if (std::regex_match(date_time, std::regex("\\d{4}[:-]\\d{2}[:-]\\d{2}(.*)"))) {
    string corrected_date_time = date_time.substr(0, 10) + " ";
    boost::algorithm::replace_all(corrected_date_time, "-", ":");  // Unified format "%Y:%m:%d %T"

    cout << date_time.substr(11) << endl;
    std::tm time_struct{};
    if (nullptr != ::strptime(date_time.c_str(), "%Y-%m-%d %T", &time_struct)) {
      int res = ::timegm(&time_struct);
      cout << res << endl;
      return "";
    }

    if (date_time.length() > 11 && std::regex_match(date_time.substr(11), std::regex(R"(\d{2}:\d{2}(:?))"))) {
      corrected_date_time += date_time.substr(11, 5) + ":00";
    } else if (date_time.length() > 11 && std::regex_match(date_time.substr(11), std::regex(R"(\d{2}(:?)(:?))"))) {
      corrected_date_time += date_time.substr(11, 2) + ":00:00";
    } else {
      corrected_date_time += "00:00:00";
    }
    return corrected_date_time;
  }
  return string{};
}

int main(int argc, char **argv) {
  string time{argv[1]};
  cout << CorrectTimeFormat(time) << endl;
  return 0;
}
