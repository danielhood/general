#include <iostream>
#include "client.h"

using namespace std;

int main(int argc, char **argv) {
	cout << "Boost Asio SSL Test" << endl << endl;

	try {
		boost::asio::io_service io_service;

		boost::asio::ip::tcp::resolver resolver(io_service);
		boost::asio::ip::tcp::resolver::query query("www.google.ca", "443");
		boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);

		boost::asio::ssl::context ctx(boost::asio::ssl::context::sslv23);
		//ctx.load_verify_file("google.com.pem");
		ctx.load_verify_file("EquifaxSecureCA.pem");

		client c(io_service, ctx, iterator);

		io_service.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Something horrible happened: " << e.what() << endl;
	}

	return 0;

}
