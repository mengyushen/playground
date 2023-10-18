#include <coroutine>
#include <iostream>

using namespace std;
// The caller-level type
struct Generator {
    // The coroutine level type
    struct promise_type {
        using Handle = std::coroutine_handle<promise_type>;
        Generator get_return_object() {
            return Generator{Handle::from_promise(*this)};
        }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        std::suspend_always yield_value(int value) {
            cout << "yield value " << value << endl;
            current_value = value;
            return {};
        }
        void unhandled_exception() { }
        int current_value;
    };
    explicit Generator(promise_type::Handle coro) : coro_(coro) {}
    ~Generator() {
        cout << "destructor"  << endl;
        if (coro_) coro_.destroy();
    }
    // Make move-only
    Generator(const Generator&) = delete;
    Generator& operator=(const Generator&) = delete;
    Generator(Generator&& t) noexcept : coro_(t.coro_) { 
        cout << "what ?"  << endl;
        t.coro_ = {};
    }
    Generator& operator=(Generator&& t) noexcept {
        cout << "move"  << endl;
        if (this == &t) return *this;
        if (coro_) coro_.destroy();
        coro_ = t.coro_;
        t.coro_ = {};
        return *this;
    }
    int get_next() {
        cout << "get next"  << endl;
        coro_.resume();
        return coro_.promise().current_value;
    }
private:
    promise_type::Handle coro_;
};
Generator myCoroutine() {
    int x = 0;
    while (true) {
        cout << "before yield"  << endl;
        co_yield x++;
        cout << "after yield"  << endl;
    }
}
int main() {
    auto c = myCoroutine();
    int x = 0;
    while ((x = c.get_next()) < 5) {
        std::cout << x << "\n";
    }
}
