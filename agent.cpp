#include "common/tcp_connection.h"
#include "common/rpc_protocol.h"
#include <iostream>

using namespace std;

int main() {
    // GLHF ;) (no está fun profe)

    net::TcpConnection connection;
    string host = "127.0.0.1";
    connection.connect(host, 8080);
    string message = "{"
        "\"id\":\"1\","
        "\"type\":\"register_agent\","
        "\"agent_id\":\"blue_agent_001\""
        "}";
    connection.sendMessage(message);
    string response = connection.receiveMessage();
    string actual_response = rpc::escapeJson(response);
    cout << actual_response << endl;


    return 0;
}