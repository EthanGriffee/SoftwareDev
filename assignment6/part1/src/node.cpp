#include "network.h"

int main(int argh, char** argv)
{
    char* input_ip;
    char* server_ip;
    int input_port, server_port;

    // Starts at 1 as the first argument in argv is a.out
    if (argh == 9) {
        for (size_t x = 1; x < argh; x += 2) {
            // handles -f flag, any input after the f flag will be considered valid
            if (strcmp(argv[x], "-ip") == 0) {
                input_ip = argv[x + 1];
            }
            else if (strcmp(argv[x], "-port") == 0) {
                input_port = atoi(argv[x + 1]);
            }
            else if (strcmp(argv[x], "-serverip") == 0) {
                server_ip = argv[x + 1];
            }
            else if (strcmp(argv[x], "-serverport") == 0) {
                server_port = atoi(argv[x + 1]);
            }
            else {
                perror("Invalid arguments");
                exit(1);
            }
            // handles everything else
        }
    }
    else {
        perror("Invalid arguments");
        exit(1);
    }

    ThreadedClient* c = new ThreadedClient(input_ip, input_port, server_ip, server_port);
    sleep(1);
    c->composeMessage("127.0.0.1:8333", "HU FIREND");
    c->readMessages();

    sleep(5);
    c->p("closing");
    c->closeSocket();

}