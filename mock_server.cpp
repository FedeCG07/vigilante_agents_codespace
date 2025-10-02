#include "common/tcp_connection.h"
#include <iostream>

using namespace std;

int main() {

    net::TcpServer server;
    server.start();
    server.acceptConnection();

    return 0;
}