#include <coroutine>
#include <iostream>

// The caller-level type
struct Task {
    // The coroutine level type
    struct promise_type {
        using Handle = std::coroutine_handle<promise_type>;
        Task get_return_object() {
          std::cout << "get_return_object\n";
          return Task{Handle::from_promise(*this)};
        }
        std::suspend_always initial_suspend() { std::cout << "initial_suspend\n"; return {}; }
        std::suspend_never final_suspend() noexcept { std::cout << "final_suspend\n"; return {}; }
        void return_void() { std::cout << "return_void\n";}
        // int return_value() { std::cout << "return_value\n"; return 222;}
        void unhandled_exception() {std::cout << "unhandled_exception\n";}
    };
	// Making Task move-only:
	Task(const Task&) = delete;
	Task& operator=(const Task&) = delete;
	Task(Task&& t) noexcept : coro_(t.coro_) { std::cout << "A\n"; t.coro_ = {}; }
	Task& operator=(Task&& t) noexcept {
		std::cout << "B\n";
		if (this == &t) return *this;
		if (coro_) coro_.destroy();
		coro_ = t.coro_;
		t.coro_ = {};
		return *this;
	}

    explicit Task(promise_type::Handle coro) : coro_(coro) {}
    ~Task() {
      std::cout << "~Task~~~\n";
      // if (coro_) {
      //   coro_.destroy();
      // }
    }

    void destroy() { std::cout << "Destroy\n"; coro_.destroy(); }
    void resume() { std::cout << "Resume\n"; coro_.resume(); }

private:
    promise_type::Handle coro_;
};

Task myCoroutine() {
    std::cout << "my Coroutine\n";
    co_return; // make it a coroutine
}
int main() {
    std::cout << "main\n";
    auto c = myCoroutine();
    std::cout << "main end\n";
    // c.resume();
    c.destroy();
}
