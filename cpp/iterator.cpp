// std::iterator example
#include <iostream>     // std::cout
#include <iterator>     // std::iterator, std::input_iterator_tag
#include <vector>
#include <algorithm>

class MyClass
{
  public:
    MyClass() : m_(), empty_{true} {}
    MyClass(int a) : m_(a), empty_{false} {}
    int m() { return m_; }
    void m(int a) { m_ = a; }
    bool empty() { return empty_; }
  private:
    int m_;
    bool empty_;
};

using namespace std;
class MyIterator : public std::iterator<std::input_iterator_tag, MyClass>
{
  MyClass* p;
  bool empty;
public:
  MyIterator() noexcept {}
  MyIterator(MyClass* x) :p(x) {}
  MyIterator(const MyIterator& mit) : p(mit.p) {}
  MyIterator& operator++() {
    ++p;return *this;
  }
  MyIterator operator++(int) {
    MyIterator tmp(*this); operator++(); return tmp;
  }
  bool operator==(const MyIterator& rhs) const {
    return p == rhs.p;
  }
  bool operator!=(const MyIterator& rhs) const {
    cerr << p->m() << endl;
    return p!=rhs.p;
  }
  MyClass& operator*() {return *p;}

};

int main () {
  MyClass numbers[]={
    MyClass{10},
    MyClass{11},
    MyClass{12},
    MyClass{13},
    MyClass{14}
  };
  vector<MyClass> vec;
  for (int i = 0; i < 5; i++) {
    vec.emplace_back(i);
  }
  MyIterator from(numbers);
  MyIterator until(numbers+5);
  MyIterator end;
  int count = 0;
  for (MyIterator it=from; it!=end; it++){
    std::cout << "---" << endl; //#(*it).m() << ' ';
    if (++count > 10) {
      break;
    }
  }
  // std::cout << '\n';

  return 0;
}
