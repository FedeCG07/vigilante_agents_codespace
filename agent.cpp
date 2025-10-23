#include "common/tcp_connection.h"
#include "common/rpc_protocol.h"
#include "common/messages.h"
#include "logic/logic.h"
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
    string register_agent_message = register_agent(agent_id);
    connection.sendMessage(register_agent_message);
    string intel;
    while (true) {
        string instruction = connection.receiveMessage();
        string id = rpc::extractStringValue(instruction, "id");
        string type = rpc::extractStringValue(instruction, "type");
        if (type == "play_turn") {
            string state = rpc::extractStringValue(instruction, "state");
            // string action = decideMove(state, intel, id);
            string action = "move north";
            string turn_message = turn_response(id, action);
            connection.sendMessage(turn_message);
        } else if (type == "receive_intel") {
            intel = rpc::extractStringValue(instruction, "intel");
            string void_response_message =  void_response(id);
            connection.sendMessage(void_response_message);
        } else if (type == "notify_death") {
            string void_response_message =  void_response(id);
            connection.sendMessage(void_response_message);
        } else if (type == "notify_game_over") {
            string void_response_message =  void_response(id);
            connection.sendMessage(void_response_message);
            cout << "This kid is out!" << endl;
            break;
        }
    }

    return 0;
}