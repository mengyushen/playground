
#include <atomic>
#include <sys/types.h>
#include <thread>
#include <unistd.h>

#include <boost/asio.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/asio/system_timer.hpp>
#include <iostream>

using namespace std;

class handler {
public:
  handler(std::size_t concurrency, boost::asio::strand &strand)
      : stopped_{false}, pool_io_{},
        strand_(strand), concurrency_{std::max(concurrency, std::size_t(1))},
        timer_{strand.get_io_service()} {
    auto service_runner = [this]() {
      while (not stopped_.load()) {
        try {
          pool_io_.run();
        } catch (const std::exception &e) {
          cerr << e.what() << endl;
        }
      }
    };
    for (std::size_t idx = 0; idx < concurrency_; ++idx) {
      cout << idx << endl;
      thread_pool_.emplace_back(service_runner);
    }

    boost::asio::spawn(strand_, [this](boost::asio::yield_context yield) {
      pool_io_.post([this] { cout << "post 1 " << getpid() << endl; });
      // while(true) {
      // timer_.expires_at(std::chrono::time_point<std::chrono::system_clock>::max());
      timer_.expires_from_now(std::chrono::seconds(1));
      boost::system::error_code ec;
      strand_.post([this] {
        sleep(1);
        cout << "Sleep 1 second -- " << getpid() << endl;
      });
      strand_.post([this] {
        sleep(1);
        cout << "Sleep 2 second -- " << getpid() << endl;
      });
      // }
    });
  }

  ~handler() {
    pool_io_.stop();

    for (auto &t : thread_pool_) {
      if (t.joinable()) {
        t.join();
      }
    }
  }

  void message1() {}

  void message2() {}

private:
  std::atomic<bool> stopped_;
  boost::asio::io_service pool_io_;
  boost::asio::strand strand_;
  vector<thread> thread_pool_;
  std::size_t concurrency_;
  boost::asio::system_timer timer_;
};

int main() {
  boost::asio::io_service io;
  boost::asio::strand main_strand{io};
  handler h(2, main_strand);
  io.run();

  return 0;
}
