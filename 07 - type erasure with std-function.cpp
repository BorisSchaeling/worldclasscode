#include <string>
#include <memory>
#include <functional>
#include <iostream>

using namespace std::literals;

struct Connection {
	virtual ~Connection() = default;
	virtual void send(const char*) = 0;
};

struct TCPConnection : public Connection {
	void send(const char *s) { std::cout << "TCP: " << s << '\n'; }
};

struct UDPConnection : public Connection {
	void send(const char *s) { std::cout << "UDP: " << s << '\n'; }
};

struct TCPConnectionFactory {
	std::unique_ptr<Connection> operator()() { return std::unique_ptr<Connection>(new TCPConnection); }
};

struct UDPConnectionFactory {
	std::unique_ptr<Connection> operator()() { return std::unique_ptr<Connection>(new UDPConnection); }
};

template <class ConnectionFactory>
void send(ConnectionFactory &conFactory) {
	auto con = conFactory();
	con->send("Hello");
}

int main(int argc, char *argv[]) {
	std::function<std::unique_ptr<Connection>()> factory;
	if (argc > 1 && argv[1] == "tcp"s) {
		factory = TCPConnectionFactory();
	}
	else {
		factory = UDPConnectionFactory();
	}
	send(factory);
}
