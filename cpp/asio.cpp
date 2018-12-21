#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/asio/system_timer.hpp>
#include <chrono>
#include <iostream>

using namespace std;

int main() {
  auto use_post = true;
  boost::asio::io_service io_service;
  boost::asio::strand strand{io_service};
  boost::asio::spawn(strand, [&strand, &io_service,
                              &use_post](boost::asio::yield_context yield) {
    if (use_post) {
      cout << __LINE__ << endl;
      io_service.post([&strand, &io_service] {
        boost::asio::spawn(strand,
                           [&io_service](boost::asio::yield_context yield) {
                             boost::asio::system_timer timer(io_service);
                             timer.expires_from_now(std::chrono::seconds(1));
                             timer.async_wait(yield);
                             cout << "Sleep 1 second -- " << endl;
                           });
      });
    } else {
      //			cout << __LINE__ << endl;
      //            boost::asio::spawn(io_service,
      //            [&io_service](boost::asio::yield_context yield){
      //				cout << __LINE__ << endl;
      //                boost::asio::system_timer timer(io_service);
      //                timer.expires_from_now(std::chrono::seconds(1));
      //                timer.async_wait(yield);
      //                cout << "Sleep 1 second" << endl;
      //            });
    }
    boost::asio::system_timer timer(io_service);
    timer.expires_from_now(std::chrono::seconds(2));
    timer.async_wait(yield);
    cout << "Sleep 2 seconds" << endl;
  });
  io_service.run();
  return 0;
}
