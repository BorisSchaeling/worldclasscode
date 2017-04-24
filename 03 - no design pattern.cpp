#include <string>
#include <iostream>

using namespace std::literals;

struct TCPConnection {
	void send(const char *s) { std::cout << "TCP: " << s << '\n'; }
};

struct UDPConnection {
	void send(const char *s) { std::cout << "UDP: " << s << '\n'; }
};

int main(int argc, char *argv[]) {
	if (argc > 1 && argv[1] == "tcp"s) {
		TCPConnection con;
		con.send("Hello");
	}
	else {
		UDPConnection con;
		con.send("Hello");
	}
}
