#include <boost/functional/value_factory.hpp>
#include <string>
#include <iostream>

using namespace std::literals;

struct TCPConnection {
	void send(const char *s) { std::cout << "TCP: " << s << '\n'; }
};

struct UDPConnection {
	void send(const char *s) { std::cout << "UDP: " << s << '\n'; }
};

using TCPConnectionFactory = boost::value_factory<TCPConnection>;
using UDPConnectionFactory = boost::value_factory<UDPConnection>;

template <class ConnectionFactory>
void send(ConnectionFactory &conFactory) {
	auto con = conFactory();
	con.send("Hello");
}

int main(int argc, char *argv[]) {
	if (argc > 1 && argv[1] == "tcp"s) {
		send(TCPConnectionFactory());
	}
	else {
		send(UDPConnectionFactory());
	}
}
