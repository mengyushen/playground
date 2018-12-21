#include <algorithm>
#include <boost/filesystem/path.hpp>
#include <fstream>
#include <functional>
#include <iostream>
#include <regex>
#include <set>
#include <string>

using namespace std;

static bool VersionCmp(const string& v1, const string& v2)
{
  std::regex version(R"(^(\d+)\.(\d+)\.(\d+)-(\d+)$)");
  // regex global_table(
  //				R"(synonym|user_info|group_info|index_queue|concept\b|administrative|team_library|)");
  std::smatch cm1;
  std::smatch cm2;
  std::regex_match(v1, cm1, version);
  std::regex_match(v2, cm2, version);
  for (auto i = 1; i < cm1.size(); ++i) {
    cout << cm1[i] << " : " << cm2[i] << endl;
    int a = stoi(cm1[i]);
    int b = stoi(cm2[i]);
    // if (cm1[i] < cm2[i]) {
    if (a < b) {
      return true;
    } else if (a > b) {
      return false;
    }
  }
  return false;
}

int main(int argc, char **argv) {
  string input{argv[1]};
  string input2{argv[2]};
  bool res = VersionCmp(input, input2);
  std::cout << "res: " << (res ? "true" : "false") << endl;
  return 0;
}


/*void sql_test(const string& input) {
  using namespace std;
  smatch sm, sm2;
  // regex global_table(
  //				R"(synonym|user_info|group_info|index_queue|concept\b|administrative|team_library|)");
  boost::filesystem::path b_path{input};

  const string file_stem = b_path.stem().string();
  const string file_extension = b_path.extension().string().substr(1);

  const string reg = "^" + file_stem + "(_(\\d)+(\\.)+)" + file_extension + "$";
  const regex target(reg, std::regex_constants::icase);
  vector<string> vectors = {"test_2.jpg",     "test_111a.jpg", "test_111.JPG",
                            "test_bb_11.jpg", "test_bb_11",    "test_1_1.jpg",
                            "test_1.jpg.jpg"};
  cout << "input: " << input << endl;
  for (const auto &v : vectors) {
    if (regex_match(v, sm, target)) {
      cout << v << " matched" << endl;
    } else {
      cout << v << " mis-matched" << endl;
    }
  }
  const string sql = "ALTER TABLE ONLY public.thumb_preview     ADD CONSTRAINT "
                     "unit_fk FOREIGN KEY (id_unit) REFERENCES public.unit(id) "
                     "MATCH FULL ON UPDATE CASCADE ON DELETE CASCADE; ALTER "
                     "TABLE ONLY public.user_info     ADD CONSTRAINT unit_fk "
                     "FOREIGN KEY (id_unit) REFERENCES public.unit(id) MATCH "
                     "FULL ON UPDATE CASCADE ON DELETE CASCADE;";
  regex replace(R"(\bpublic(\.)(?!user_info))");
  const string schema = "user_8";
  cout << regex_replace(sql, replace, schema + "$1");

}
*/
