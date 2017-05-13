#include <memory>
#include <iostream>

template <typename Concept>
struct any : Concept {
	template <typename T>
	void operator=(T t) { o = std::make_unique<object<T>>(t); }
};

#define MEMBER_FUNCTION(x, y)												\
template <typename T>														\
struct x;																	\
template <typename ReturnType, typename... Args>							\
struct x<ReturnType(Args...)> {												\
	ReturnType y(Args... args) {											\
		return o->invoke(args...);											\
	}																		\
protected:																	\
	struct object_base {													\
		virtual ~object_base() = default;									\
		virtual ReturnType invoke(Args...) = 0;								\
	};																		\
	template <class T>														\
	struct object : object_base {											\
		object(T t) : t(t) {}												\
		ReturnType invoke(Args... args) override { return t.y(args...); }	\
	private:																\
		T t;																\
	};																		\
	std::unique_ptr<object_base> o;											\
};

struct TCPConnection {
	void send(const char *s) { std::cout << "TCP: " << s << '\n'; }
};

struct UDPConnection {
	void send(const char *s) { std::cout << "UDP: " << s << '\n'; }
};

MEMBER_FUNCTION(has_send, send)
using Connection = any<has_send<void(const char*)>>;

int main(int argc, char *argv[]) {
	Connection c;
	c = TCPConnection();
	c.send("Hello");
	c = UDPConnection();
	c.send("Hello");
}
