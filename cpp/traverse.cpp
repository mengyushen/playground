#include <utility>
#include <boost/filesystem.hpp>
#include <boost/locale.hpp>
#include <boost/locale/collator.hpp>
#include <locale>
#include <iostream>
#include <string>
#include <boost/algorithm/string/classification.hpp>
#include <boost/locale.hpp>
#include <stack>


#define foreach BOOST_FOREACH
namespace fs = boost::filesystem;
namespace locale = boost::locale;
using namespace std;
bool isDefaultLocaleInited = false;
string NormalizeUnicodeUTF8String(const string& input)
{
  if (not isDefaultLocaleInited) {
    std::locale global_locale = boost::locale::generator().generate("en_US.UTF-8");
    std::locale::global(global_locale);
    isDefaultLocaleInited = true;
  }

  std::string upper_input = boost::locale::to_upper(input);
  std::wstring wide_input = boost::locale::conv::utf_to_utf<wchar_t>(upper_input);

  std::wstring normalized_input;
  normalized_input = boost::locale::normalize(wide_input, boost::locale::norm_nfd);

  string result = boost::locale::conv::utf_to_utf<char>(normalized_input);
  return result;
}

bool UnicodeCompare(const string& str1, const string& str2)
{
  return NormalizeUnicodeUTF8String(str1) == NormalizeUnicodeUTF8String(str2);
}

string Test(const string& prefix, const vector<string> folders)
{
  fs::directory_iterator current{fs::path{prefix}};
  fs::directory_iterator end;
  int ptr = 0;
  auto folder = folders.empty() ? fs::path{""} : folders.at(ptr);
  size_t size = folders.size();

  while(current != end && !folder.empty()) {
    if (is_directory(current->status())) {
      if (!current->path().stem().empty() && UnicodeCompare(current->path().stem().string(), folder.string())) {
        if (++ptr < size) {
          current = fs::directory_iterator(current->path());
          folder = folders.at(ptr);
          continue;
        } else {
          break;
        }
      }
    }
    current++;
  }
  if (current == end) {
    cout << "Not found" << endl;
    return string();
  }
  vector<string> output;
  for (auto i = current->path().begin(); i != current->path().end(); i++) {
    output.emplace_back((*i).string());
  }
  
  vector<string> ret{output.begin() + output.size() - size, output.end()};
  for (auto a: ret) {
    cout << "__" << a << endl;
  }
  return current->path().string();
}


int main (int argc, char* argv[]) {
  string top{argv[1]};
  vector<string> folders{"a", "b", "temP", "DOC"};
  if (not isDefaultLocaleInited) {
    std::locale global_locale = boost::locale::generator().generate("en_US.UTF-8");
    std::locale::global(global_locale);
    isDefaultLocaleInited = true;
  }
  // locale::comparator<char,locale::collator_base::secondary> cmpr;
  // cout << "current: " << Test(top, folders) << endl;
  fs::path test{"/Moments/a/b/123.jpg"};
  cout << test.parent_path().relative_path() << endl; 
  cout << test.root_path() << endl; 
}
