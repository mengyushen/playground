#include <fstream>
#include <iostream>
#include <regex>
#include <set>
#include <string>
#include <algorithm>
#include <functional>

using namespace std;

int main () {
	using namespace std;
	ifstream input("/home/tcgarita/database-dali.sql");
	set<std::string> skip_table = {"synonym", "user_info", "group_info", "concept", "administrative", "index_queue"};
	string output;
	if (input.is_open()) {
		string sql, line, sql_type("");
		regex skip_global_trigger("CREATE TRIGGER (create_user_schema_trigger|delete_user_schema_trigger)$");
		// regex skip_statement("(CREATE|ALTER) (FUNCTION|.*? OWNER) .*?(;?)$");
		regex skip_statement("ALTER .*? OWNER .*?(;?)$");
		regex function("CREATE FUNCTION .*?(;?)$");
		regex statement(
			R"((CREATE|ALTER) (?:TABLE|VIEW|TRIGGER|INDEX|RULE).*?(?:(?:ON|TO)?\s*public\.(.*?))[ |(].*$)");
		regex insert_statement("INSERT INTO .*$");
		regex remove_public(
			R"(\bpublic\.(?!synonym|user_info|group_info|index_queue|concept\b|administrative))");
		while (getline(input, line)) {
			smatch sm;
			if (!line.compare(0, 2, "--") || !line.size()) {
				continue;
			}
			if (regex_match(line, sm, skip_statement) || regex_match(line, sm, skip_global_trigger)) {
				sql_type = sm.str(3) == ";" ? string() : sm.str(2);
			} else if (regex_match(line, sm, function)) {
				sql_type = "FUNCTION";
				sql += line + " ";
			} else if (sql_type == "FUNCTION" && (line.compare(line.size() - 3, 3, "$$;") == 0)) {
				output += regex_replace(sql + line, remove_public, "");
				output += "\n";
				sql_type = "";
				sql = "";
			} else if (sql_type == "" && !line.compare(line.size() - 1, 1, ";")) {
				sql = sql + line;
				if (regex_match(sql, sm, statement) && skip_table.find(sm.str(2)) == skip_table.end()) {
					output += regex_replace(sm.str(0), remove_public, "");
					output += "\n";
				} else if (regex_match(sql, sm, insert_statement)) {
					output += sm.str(0) + "\n";
				} else {
					// cerr << "no match: " << sql << endl;
				}
				sql_type = "";
				sql = "";
			} else {
				sql += line + " ";
			}
		}
		input.close();
	}
	cout << output << endl;
	return 0;
}
