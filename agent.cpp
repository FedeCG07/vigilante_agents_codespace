#include "common/tcp_connection.h"
#include "common/rpc_protocol.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    string host = "127.0.0.1";
    int port = 8080;
    string agent_id = "backup_agent_id";

    if (argc > 1) {
        host = argv[1];
    }
    if (argc > 2) {
        port = stoi(argv[2]);
    }
    if (argc > 3) {
        agent_id = argv[3];
    }

    // GLHF ;) (no está fun profe)

    net::TcpConnection connection;
    connection.connect(host, port);
    string register_agent_message = "{"
        "\"id\":\"1\","
        "\"type\":\"register_agent\","
        "\"agent_id\":" + agent_id +
        "}";
    connection.sendMessage(register_agent_message);
    while (true) {
        string response = connection.receiveMessage();
        string id = rpc::extractStringValue(response, "id");
        if (rpc::extractStringValue(response, "type") == "play_turn") {
            string turn_message = "{"
                "\"id\":" + id + ","
                "\"action\":\"move north\""
                "}";
            connection.sendMessage(turn_message);
        }
    }


    return 0;
}