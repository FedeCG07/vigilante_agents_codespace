#include "common/tcp_connection.h"
#include <iostream>

using namespace std;

int main() {

    net::TcpServer server;
    server.start();
    cout << server.acceptConnection() << endl;

    return 0;
}