#include <memory>
#include <iostream>

template <typename T>
class function;

template <typename ReturnType, typename... Args>
class function<ReturnType(Args...)> {
public:
	template <typename T>
	void operator=(T t) { c = std::make_unique<callable<T>>(t); }
	ReturnType operator()(Args... args) { return c->invoke(args...); }

private:
	struct callable_base {
		virtual ~callable_base() = default;
		virtual ReturnType invoke(Args...) = 0;
	};

	template <class T>
	struct callable : callable_base {
		callable(T t) : t(t) {}
		ReturnType invoke(Args... args) override { return t(args...); }

	private:
		T t;
	};

	std::unique_ptr<callable_base> c;
};

void hello() {
	std::cout << "Hello function\n";
}

struct Hello {
	void operator()() const {
		std::cout << "Hello class\n";
	}
};

int main(int argc, char *argv[]) {
	function<void()> f;
	f = hello;
	f();
	f = Hello();
	f();
}
