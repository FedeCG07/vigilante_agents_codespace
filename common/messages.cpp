#include "messages.h"

using namespace std;

string register_agent(string agent_id) {
    string register_agent_message = "{"
        "\"id\":\"1\","
        "\"type\":\"register_agent\","
        "\"agent_id\":\"" + agent_id + "\""
        "}";

    return register_agent_message;
}

string void_response(string id) {
    string void_response = "{"
        "\"id\":\"" + id + "\","
        "\"status\":\"ok\""
        "}";

    return void_response;
}

string turn_response(string id, string action) {
    string turn_response = "{"
        "\"id\":\"" + id + "\","
        "\"action\":\"" + action + "\""
        "}";

    return turn_response;
}