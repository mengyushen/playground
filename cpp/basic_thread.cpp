
#include <boost/asio.hpp>
#include <iostream>
#include <unistd.h>
#include <thread>
#include <vector>
#include <string>
#include <utility> 
#include <sstream>

using namespace std;
using namespace boost::asio;

struct A {
  int id;
  string name;
};

class Worker {
  io_service io_;
}

int main()
{
    vector<thread> thread_pool_; 
    int count = 5;
	for (int i = 0; i < count; i++) {
      A a;
      a.id = i;
      std::stringstream ss;
      ss << "thread " << i;
      a.name = ss.str();
	  auto service_runner = [i, count, a = std::move(a)]() {
        sleep(count - i);
        cout << "thread name:" << a.name << endl;
        cout << "thread id:" << a.id << endl;
        cout.flush();
	  };
      cout << "thread name again:" << a.name << endl;
      thread_pool_.emplace_back(service_runner);
    }

    cout << "Hello ";
    cout.flush();
    for (auto& t : thread_pool_) {
      if (t.joinable()) {
        t.join();
      }
    }

    cout << "\n\n\n";//跳三行

    return 0;
}
