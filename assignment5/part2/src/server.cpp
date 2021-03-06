#include "network.h"


int main(int argh, char** argv)
{
    char empty[] = "";
    char* input_ip = &empty[0];


    // Starts at 1 as the first argument in argv is a.out
    if (argh == 3) {
        // handles -f flag, any input after the f flag will be considered valid
        if (strcmp(argv[1], "-ip") == 0) {
            input_ip = argv[2];
        }
        else {
            perror("Invalid arguments");
            exit(1);
        }
        // handles everything else
    }


    ThreadedServer* s = new ThreadedServer(input_ip);
    s->waitForConnectionsAndRead();

    sleep(10);
    s->p("closing");
    s->closeSocket();
}