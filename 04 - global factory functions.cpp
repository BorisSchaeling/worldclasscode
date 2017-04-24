#include <string>
#include <iostream>

using namespace std::literals;

struct TCPConnection {
	void send(const char *s) { std::cout << "TCP: " << s << '\n'; }
};

struct UDPConnection {
	void send(const char *s) { std::cout << "UDP: " << s << '\n'; }
};

TCPConnection make_tcp_connection() { return TCPConnection(); }
UDPConnection make_udp_connection() { return UDPConnection(); }

template <class ConnectionFactory>
void send(ConnectionFactory &conFactory) {
	auto con = conFactory();
	con.send("Hello");
}

int main(int argc, char *argv[]) {
	if (argc > 1 && argv[1] == "tcp"s) {
		send(make_tcp_connection);
	}
	else {
		send(make_udp_connection);
	}
}
