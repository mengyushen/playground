#include <boost/tokenizer.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace boost;

int main(int, char *argv[]) {
  // string text{argv[1]};
  string text{"\"ABC\", \"b\\\\\"a\\\"c test"};

  string separator1("");     // dont let quoted arguments escape themselves
  string separator2(" ");    // split on spaces
  string separator3("\"\'"); // let it have quoted arguments

  escaped_list_separator<char> els(separator1, separator2, separator3);
  tokenizer<escaped_list_separator<char>> tokens(text, els);
  for (const auto &t : tokens) {
    cout << t << "." << endl;
  }
}
