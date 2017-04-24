#include <string>
#include <memory>
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
	virtual std::unique_ptr<Connection> make() = 0;
};

struct TCPConnectionFactory : public ConnectionFactory {
	std::unique_ptr<Connection> make() override { return std::make_unique<TCPConnection>(); }
};

struct UDPConnectionFactory : public ConnectionFactory {
	std::unique_ptr<Connection> make() override { return std::make_unique<UDPConnection>(); }
};

void send(ConnectionFactory &conFactory) {
	std::unique_ptr<Connection> con = conFactory.make();
	con->send("Hello");
}

int main(int argc, char *argv[]) {
	std::unique_ptr<ConnectionFactory> conFactory;
	if (argc > 1 && argv[1] == "tcp"s) {
		conFactory = std::make_unique<TCPConnectionFactory>();
	}
	else {
		conFactory = std::make_unique<UDPConnectionFactory>();
	}
	send(*conFactory);
}
