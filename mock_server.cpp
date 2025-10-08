#include "common/tcp_connection.h"
#include "common/rpc_protocol.h"
#include <iostream>

using namespace std;

int main() {

    net::TcpServer server;
    server.start();
    unique_ptr<net::TcpConnection> connection = server.acceptConnection();
    string message = connection->receiveMessage();
    string void_response = "{"
        "\"id\":\"1\","
        "\"status\":\"ok\""
        "}";
    connection->sendMessage(void_response);

    return 0;
}