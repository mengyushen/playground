#include <iostream>
#include <string>
#include <initializer_list>

using namespace std;

class Widget {
  public:
    Widget(int i, bool b) {
      cout << "ctor1" << endl;
    };
    Widget(int i, double d) {
      cout << "ctor2" << endl;
    };
    
    // ctor3
    Widget(std::initializer_list<long double> il) {
      cout << "ctor3" << endl;
    };

    Widget(Widget&& a) {
      cout << "move ctor" << endl;
    };

    Widget(const Widget& a) {
      cout << "copy ctor" << endl;
    };
    
    operator float() const {
      cout << "convert to float" << endl;
    };       // convert to float
};


int main(int argc, char** argv)
{
    cout << "w1 "; 
	Widget w1(10, true);
    cout << "w2 "; 
	Widget w2{10, true};	

    cout << "w3 "; 
	Widget w3(10, 0.4);
    cout << "w4 "; 
	Widget w4{10, 0.4};	
    
    cout << "w5 "; 
    Widget w5(w4);
    cout << "w6 "; 
    Widget w6{w4};

    cout << "w7 "; 
    Widget w7(std::move(w4));

    cout << "w8 "; 
    Widget w8{std::move(w4)};
}
