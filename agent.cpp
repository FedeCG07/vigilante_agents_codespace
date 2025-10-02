#include "common/tcp_connection.h"
#include <iostream>

using namespace std;

int main() {
    // GLHF ;) (no está fun profe)

    net::TcpConnection connection;
    string host = "192.168.56.1";
    connection.connect(host, 8080);
    cout << connection.isConnected() << endl;

    return 0;
}