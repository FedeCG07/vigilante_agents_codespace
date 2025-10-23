#include "logic.h"
#include "common/rpc_protocol.h"
#include "common/game_state.h"
#include <vector>

bool isMovePossible(const int x, const int y, const string map, const string config) {
    int width = rpc::extractIntValue(config, "map_width");
    int position = (y - 1) * width + x;
    return (map.at(position) == '.' or map.at(position) == '^');
}

vector<string> getAgentsPosition (const string agents) {
    vector<string> agent_positions;
    rpc::extractStringValue(agents, "position");

    return agent_positions;
}

string decideMove(const string state, const string intel, const string id) {
    game::GameState game_state = rpc::deserializeGameState(state);
    game::Agent me = game_state.agents[0];
    for (game::Agent agent : game_state.agents) {
        if (agent.id == id) {
            me = agent;
        }
    }
/*     
    if (!game_state.bases.empty()) {
        if (game_state.bases[0].team != me.team and ) {
            
        }
    } */
}