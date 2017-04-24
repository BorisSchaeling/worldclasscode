#include <string>
#include <iostream>

using namespace std::literals;

struct Connection {
	virtual ~Connection() = default;
	virtual void send(const char*) = 0;
};

struct TCPConnection : public Connection {
	void send(const char *s) override { std::cout << "TCP: " << s << '\n'; }
};

struct UDPConnection : public Connection {
	void send(const char *s) override { std::cout << "UDP: " << s << '\n'; }
};

struct ConnectionFactory {
	virtual ~ConnectionFactory() = default;
	virtual Connection *make() = 0;
};

struct TCPConnectionFactory : public ConnectionFactory {
	Connection *make() override { return new TCPConnection(); }
};

struct UDPConnectionFactory : public ConnectionFactory {
	Connection *make() override { return new UDPConnection(); }
};

void send(ConnectionFactory *conFactory) {
	Connection *con = conFactory->make();
	con->send("Hello");
	delete con;
}

int main(int argc, char *argv[]) {
	ConnectionFactory *conFactory;
	if (argc > 1 && argv[1] == "tcp"s) {
		conFactory = new TCPConnectionFactory();
	}
	else {
		conFactory = new UDPConnectionFactory();
	}
	send(conFactory);
	delete conFactory;
}
