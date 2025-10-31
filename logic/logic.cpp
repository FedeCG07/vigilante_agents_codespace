#include "logic.h"
#include "common/rpc_protocol.h"
#include "common/game_state.h"
#include <vector>
#include <sstream>

bool isMovePossible(const int x, const int y, const string map, const string config) {
    int width = rpc::extractIntValue(config, "map_width");
    int position = (y - 1) * width + x;
    return (map.at(position) == '.' or map.at(position) == '^');
}

string decideMove(const string state, const string intel, const string id) {
    game::GameState game_state = rpc::deserializeGameState(state);
    game::Agent me = game_state.agents[0];

    for (auto& agent : game_state.agents) {
        if (agent.id == id) {
            me = agent;
            break;
        }
    }

    int known_base_x = -1, known_base_y = -1;
    if (intel.rfind("ENEMY_BASE", 0) == 0) { // intel empieza con ENEMY_BASE
        stringstream ss(intel);
        string tag;
        ss >> tag >> known_base_x >> known_base_y;
    }

    int seen_base_x = -1, seen_base_y = -1;
    for (auto& base : game_state.bases) {
        if (base.team != me.team) {
            seen_base_x = base.position.x;
            seen_base_y = base.position.y;

            if (known_base_x == -1) {
                string msg = "ENEMY_BASE " + to_string(seen_base_x) + " " + to_string(seen_base_y);
                return "send_message:" + msg;
            }
        }
    }

    game::Agent* nearest_enemy = nullptr;
    int nearest_dist = 9999;
    for (auto& agent : game_state.agents) {
        if (agent.team != me.team) {
            int dist = abs(agent.position.x - me.position.x) + abs(agent.position.y - me.position.y);
            if (dist < nearest_dist) {
                nearest_enemy = &agent;
                nearest_dist = dist;
            }
        }
    }

    if (nearest_enemy && nearest_dist == 1 && me.hp > 30) {
        string dir;
        if (nearest_enemy->position.x > me.position.x) dir = "east";
        else if (nearest_enemy->position.x < me.position.x) dir = "west";
        else if (nearest_enemy->position.y > me.position.y) dir = "south";
        else dir = "north";
        return "attack_" + dir;
    }

    if (nearest_enemy && nearest_dist <= 2 && me.hp <= 30) {
        string dir;
        if (nearest_enemy->position.x > me.position.x) dir = "west";
        else if (nearest_enemy->position.x < me.position.x) dir = "east";
        else if (nearest_enemy->position.y > me.position.y) dir = "north";
        else dir = "south";
        return "move_" + dir;
    }

    if (known_base_x != -1) {
        int dx = known_base_x - me.position.x;
        int dy = known_base_y - me.position.y;

        string dir;
        if (abs(dx) + abs(dy) == 1) {
            if (dx == 1) dir = "east";
            else if (dx == -1) dir = "west";
            else if (dy == 1) dir = "south";
            else dir = "north";

            return "attack_" + dir;
        }

        if (abs(dx) > abs(dy)) {
            dir = (dx > 0) ? "east" : "west";
        } else {
            dir = (dy > 0) ? "south" : "north";
        }

        return "walk_" + dir;
    }

    // Exploración aleatoria si no hay info
    vector<string> dirs = {"north", "south", "east", "west"};
    srand(time(NULL) + me.position.x * 31 + me.position.y * 17); // más variación
    string chosen = dirs[rand() % 4];

    return "walk_" + chosen;
}