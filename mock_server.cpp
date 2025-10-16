#include "common/tcp_connection.h"
#include "common/rpc_protocol.h"
#include "common/messages.h"
#include <iostream>

using namespace std;

int main() {

    net::TcpServer server;
    server.start();
    unique_ptr<net::TcpConnection> connection = server.acceptConnection();
    string message = connection->receiveMessage();
    string agent_id = rpc::extractStringValue(message, "agent_id");
    string id = rpc::extractStringValue(message, "id");
    string void_response_message = void_response(id);
    connection->sendMessage(void_response_message);

    string turn_message = "{"
        "\"id\":\"1\","
        "\"type\":\"play_turn\","
        "\"agent_id\":" + agent_id +
        "}";
    
    string game_over_message = "{"
        "\"id\":\"1\","
        "\"type\":\"notify_game_over\","
        "\"winning_team\":1"
        "}";

    connection->sendMessage(game_over_message);
    message = connection->receiveMessage();
    string move = rpc::extractStringValue(message, "action");

    return 0;
}