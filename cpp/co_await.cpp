#include <chrono>
#include <coroutine>
#include <thread>
#include <iostream>

using namespace std;

struct Sleeper {
    bool await_ready() const {
      cout << "await ready" << endl;
      return false;
    }
    void await_suspend(std::coroutine_handle<> h) const {
        cout << "await suspend" << endl;
        auto t = std::jthread([h,l = length] {
            cout << "await suspend in thread" << endl;
            std::this_thread::sleep_for(l);
            cout << "before resume" << endl;
            h.resume();
            cout << "after resume" << endl;
        });
    }
    void await_resume() const {
      cout << "await resume" << endl;
    }
    const std::chrono::duration<int, std::milli> length;
};

// The caller-level type
struct Task {
    // The coroutine level type
    struct promise_type {
        using Handle = std::coroutine_handle<promise_type>;
        Task get_return_object() {
            cout << "get return object" << endl;
            return Task{Handle::from_promise(*this)};
        }
        std::suspend_never initial_suspend() { cout << "inital" << endl; return {}; }
        std::suspend_never final_suspend() noexcept { cout << "final" << endl; return {}; }

//		std::suspend_always await_transform(std::suspend_always s) {
//            cout << "await transform" << endl;
//  			return std::suspend_always{};
//  		}
  
        void return_void() { cout << "return void" << endl; }
        void unhandled_exception() { }
    };
    explicit Task(promise_type::Handle coro) : coro_(coro) {}
    void destroy() { coro_.destroy(); }
    void resume() { coro_.resume(); }
private:
    promise_type::Handle coro_;
};

Task myCoroutine() {
    using namespace std::chrono_literals;
    cout << "Begin Sleep" << endl;
    auto before = std::chrono::steady_clock::now();
    co_await Sleeper{5s};
    cout << "End Sleep" << endl;
    auto after = std::chrono::steady_clock::now();
    std::cout << "Slept for " << (after-before) / 1ms << " ms\n";
}


int main() {
    auto x = myCoroutine();
}

