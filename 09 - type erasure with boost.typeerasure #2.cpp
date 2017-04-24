#include <boost/type_erasure/any.hpp>
#include <boost/type_erasure/member.hpp>
#include <boost/type_erasure/builtin.hpp>
#include <boost/type_erasure/relaxed.hpp>
#include <string>
#include <iostream>

using namespace std::literals;

struct TCPConnection {
	void send(const char *s) { std::cout << "TCP: " << s << '\n'; }
};

struct UDPConnection {
	void send(const char *s) { std::cout << "UDP: " << s << '\n'; }
};

struct TCPConnectionFactory {
	TCPConnection make() { return TCPConnection(); }
};

struct UDPConnectionFactory {
	UDPConnection make() { return UDPConnection(); }
};

template <class ConnectionFactory>
void send(ConnectionFactory &conFactory) {
	auto con = conFactory.make();
	con.send("Hello");
}

BOOST_TYPE_ERASURE_MEMBER((has_send), send)
using Connection = boost::type_erasure::any<boost::mpl::vector<has_send<void(const char*)>, boost::type_erasure::copy_constructible<>>>;

BOOST_TYPE_ERASURE_MEMBER((has_make), make)
using ConnectionFactory = boost::type_erasure::any<boost::mpl::vector<has_make<Connection()>, boost::type_erasure::copy_constructible<>, boost::type_erasure::relaxed>>;

int main(int argc, char *argv[]) {
	ConnectionFactory factory;
	if (argc > 1 && argv[1] == "tcp"s) {
		factory = TCPConnectionFactory();
	}
	else {
		factory = UDPConnectionFactory();
	}
	send(factory);
}
