#include <iostream>
#include <boost/date_time/local_time/local_time.hpp>
#include <boost/thread.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/local_time/local_date_time.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/posix_time/posix_time_duration.hpp>

using namespace boost::posix_time;
using namespace std;

void thread_time();
void time_diff();

static boost::posix_time::ptime lastUpdated(boost::gregorian::date(1970,1,1));

int main(int argc, char* argv[])
{
    time_diff();
    boost::this_thread::sleep(boost::posix_time::millisec(2000));
    time_diff();
    return 0;
}

void time_diff()
{
    ptime now = second_clock::local_time();
    time_duration diff = now - lastUpdated;
    cout << "time diff: " << diff.total_seconds() << std::endl;
    lastUpdated = now;
}

void thread_time()
{
    boost::posix_time::ptime t1 = boost::posix_time::second_clock::local_time();
    boost::this_thread::sleep(boost::posix_time::millisec(500));
    boost::posix_time::ptime t2 = boost::posix_time::second_clock::local_time();
    boost::posix_time::time_duration diff = t2 - t1;
    std::cout << diff.total_milliseconds() << std::endl;

    boost::posix_time::ptime mst1 = boost::posix_time::microsec_clock::local_time();
    boost::this_thread::sleep(boost::posix_time::millisec(500));
    boost::posix_time::ptime mst2 = boost::posix_time::microsec_clock::local_time();
    boost::posix_time::time_duration msdiff = mst2 - mst1;
    std::cout << msdiff.total_milliseconds() << std::endl;
}
