#include <unistd.h>
#include <stdlib.h>
#include <iostream> 
#include <signal.h>
#include <mongoose/Server.h>
#include <mongoose/WebController.h>
#include <mongoose/JsonController.h>

using namespace std;
using namespace Mongoose;

class MyJsonController : public JsonController
{
public:
	void handle_json(Request &request, StreamResponse &response) {
		//mg_send_status(conn, 200);
		//mg_send_header(conn, "Content-type", "text/json");
		

		response << "{\"greeting\"{\"message\":\"hello\",\"message2\":\"there\"}}" << endl;
		//mg_send_data(conn, response, strlen(response));
	}

	void setup()
	{
		addRoute("GET", "/json", MyJsonController, handle_json);
	}
};

//static int handle_content(struct mg_connection *conn) {
//	mg_send_status(conn, 200);	
//	mg_send_header(conn, "Content-type", "text/html");
//
//	static const char *response = 
//		"<html><head><title>Rest Server</title></head><body><h1>Hello from restsvr</h1></body></html>\n";
//	mg_send_data(conn, response, strlen(response));
//	return 1;
//}

int main(void) {
	cout << "Initializing controler..." << endl;

	MyJsonController jsonController;
	Server server(8888);
	server.registerController(&jsonController);
	
	cout << "Starting server on port 8888..." << endl;
	server.start();

	cout << "Server started" << endl;

	while (1){
		sleep(10);
	}
/*
        struct mg_server *server = mg_create_server(NULL);
        mg_set_option(server, "documnt_root", ".");
        mg_set_option(server, "listening_port", "8888");
        mg_add_uri_handler(server, "/json", &handle_json);
        mg_add_uri_handler(server, "/content", &handle_content);
        for (;;) mg_poll_server(server, 1000);
        mg_destroy_server(&server);
*/
        return 0;
}

