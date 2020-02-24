#include "../src/network.h"

void client_server_test() {
    Server* s = new Server("127.0.0.1");
    Client* c = new Client("127.0.0.2");
    s->sendMessage("127.0.0.2", "test");
    c->sendMessage("test2");
}


int main(int argc, char **argv) {
    client_server_test();
}