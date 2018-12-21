
#include <algorithm>
#include <boost/algorithm/string/join.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

int main() {
  const string schema_{"user_1"};
  unordered_set<int32_t> concept_ids{1, 2, 3, 4, 5, 5, 1, 2};
  // unordered_set<int32_t> concept_ids{};

  vector<string> ids{concept_ids.size()};
  std::transform(concept_ids.begin(), concept_ids.end(), ids.begin(),
                 [](int32_t id) {
                   cout << id << endl;
                   return std::to_string(id);
                 });
  string conditions = boost::algorithm::join(ids, ",");
  cout << "size : " << ids.size() << endl;

  string search_timeline{schema_ + ".search_timeline"};
  string concept_timeline_view{schema_ + ".concept_timeline_view"};

  std::stringstream sql;
  sql << "INSERT INTO " << search_timeline
      << " SELECT id_item, type, id_unit, takentime, place "
      << " FROM " << concept_timeline_view << " WHERE id_concept && ARRAY["
      << conditions << "]";
  cout << sql.str() << endl;
}
