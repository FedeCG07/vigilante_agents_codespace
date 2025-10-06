#include "common/tcp_connection.h"
#include <iostream>

using namespace std;

int main() {
    // GLHF ;) (no está fun profe)

    net::TcpConnection connection;
    string host = "127.0.0.1";
    connection.connect(host, 8080);
    cout << connection.isConnected() << endl;

    return 0;
}