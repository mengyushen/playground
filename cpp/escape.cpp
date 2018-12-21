#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <iostream>

using namespace std;
using namespace boost;

template <typename T> T repeat_mark() {
  return (std::numeric_limits<T>::max)();
};

struct find_compressF {
  // Construction
  find_compressF() {}

  // Operation
  template <typename ForwardIteratorT>
  iterator_range<ForwardIteratorT> operator()(ForwardIteratorT Begin,
                                              ForwardIteratorT End) const {
    typedef ForwardIteratorT input_iterator_type;
    typedef
        typename boost::detail::iterator_traits<input_iterator_type>::value_type
            value_type;
    typedef iterator_range<input_iterator_type> result_type;

    // begin of the matching segment
    input_iterator_type MStart = End;
    // Repetition counter
    value_type Cnt = 0;

    // Search for a sequence of repetitive characters
    for (input_iterator_type It = Begin; It != End;) {
      input_iterator_type It2 = It++;

      if (It == End || Cnt >= (std::numeric_limits<value_type>::max)()) {
        return result_type(MStart, It);
      }

      if (*It == *It2) {
        if (MStart == End) {
          // Mark the start
          MStart = It2;
        }

        // Increate repetition counter
        Cnt++;
      } else {
        if (MStart != End) {
          if (Cnt > 2)
            return result_type(MStart, It);
          else {
            MStart = End;
            Cnt = 0;
          }
        }
      }
    }

    return result_type(End, End);
  }
};

template <typename SeqT> struct format_compressF {
private:
  typedef SeqT result_type;
  typedef typename SeqT::value_type value_type;

public:
  // Construction
  format_compressF(){};

  // Operation
  template <typename ReplaceT>
  result_type operator()(const ReplaceT &Replace) const {
    SeqT r;
    if (!Replace.empty()) {
      r += "!";
      r += *(Replace.begin());
      //			r.push_back(Replace);
      //            r.push_back( repeat_mark<value_type>() );
      //            r.push_back( *(Replace.begin()) );
    }

    return r;
  }
};

int main(int argc, char **argv) {
  std::string s(argv[1]);

  std::cout << s << std::endl;

  boost::find_format_all(s, boost::token_finder(boost::is_any_of("!_%")),
                         format_compressF<string>());

  // boost::find_format_all(s, find_compressF(), format_compressF<string>() );
  cout << s << endl;
  return 0;
}
