#include "common/tcp_connection.h"
#include "common/rpc_protocol.h"
#include <iostream>

using namespace std;

int main() {

    string void_response = "{"
        "\"id\":\"1\","
        "\"status\":\"ok\""
        "}";

    net::TcpServer server;
    server.start();
    unique_ptr<net::TcpConnection> connection = server.acceptConnection();
    string message = connection->receiveMessage();
    string agent_id = rpc::extractStringValue(message, "agent_id");
    connection->sendMessage(void_response);

    string turn_message = "{"
        "\"id\":\"1\","
        "\"type\":\"play_turn\","
        "\"agent_id\":" + agent_id +
        "}";

    connection->sendMessage(turn_message);
    message = connection->receiveMessage();
    string move = rpc::extractStringValue(message, "action");

    return 0;
}