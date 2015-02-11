#include "client.h"

#include <boost/bind.hpp>

using namespace std;

client::client (
			boost::asio::io_service& io_service,
			boost::asio::ssl::context& context,
			boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
				: socket_(io_service, context) {

	socket_.set_verify_mode(boost::asio::ssl::verify_peer);
	socket_.set_verify_callback(
			boost::bind(&client::verify_certificate, this, _1, _2));

	boost::asio::async_connect(socket_.lowest_layer(), endpoint_iterator,
			boost::bind(&client::handle_connect, this, boost::asio::placeholders::error));

}
	
bool client::verify_certificate(bool preverified, boost::asio::ssl::verify_context& ctx) {
	char subject_name[256];
  X509* cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
	X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);
	cout << "Verifying " << subject_name << "\n";

	return preverified;
}

void client::handle_connect(const boost::system::error_code& error) {
	if (!error)
	{
		socket_.async_handshake(boost::asio::ssl::stream_base::client,
				boost::bind(
					&client::handle_handshake, this,
					boost::asio::placeholders::error));
	}
	else
	{
		cout << "Connect failed: " << error.message() << "\n";
	}
}

void client::handle_handshake(const boost::system::error_code& error) {
	if (!error)
	{
		//cout << "Enter message: ";
		//cin.getline(request_, max_length);
		//
		strncpy(request_, "GET / HTTP/1.1\r\nHost: www.google.ca\r\nAccept: text/html\r\nConnection: close\r\nCache-Control: no-cache\r\n\r\n", sizeof request_);

		size_t request_length = strlen(request_);

		cout << endl << "Sending message:" << request_ << endl;

		boost::asio::async_write(socket_,
				boost::asio::buffer(request_, request_length),
				boost::bind(
					&client::handle_write, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
	}
	else
	{
		cout << "Handshake failed: " << error.message() << "\n";
	}
}

void client::handle_write(const boost::system::error_code& error, size_t bytes_transferred) {
	if (!error)
	{
		boost::asio::async_read(socket_,
				response_, boost::asio::transfer_at_least(1),
				boost::bind(
					&client::handle_read, this,
					boost::asio::placeholders::error));
	}
	else
	{
		cout << "Write failed: " << error.message() << "\n";
	}	
}

void client::handle_read(const boost::system::error_code& error) {
	if (!error)
	{
		cout << "Reply: ";
		cout << &response_;

		// Continue
		boost::asio::async_read(socket_,
				response_, boost::asio::transfer_at_least(1),
				boost::bind(&client::handle_read, this,
					boost::asio::placeholders::error));
	}
  else if (error.category() == boost::asio::error::get_ssl_category() &&
			error.value() == ERR_PACK(ERR_LIB_SSL, 0, SSL_R_SHORT_READ)) {
		// -> not a real error:
		cout << endl << "Interpreting short read error as completion" << endl;
	}
	else if (error != boost::asio::error::eof)
	{
		cout << "Read failed: " << error.message() << "\n";
	}
}

