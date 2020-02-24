#include "network.h"


int main(int argh, char** argv)
{
    char empty[] = "";
    char* input_ip = &empty[0];
    int input_port; 


    // Starts at 1 as the first argument in argv is a.out
    if (argh == 5) {
        // handles -f flag, any input after the f flag will be considered valid
        if (strcmp(argv[1], "-ip") == 0) {
            input_ip = argv[2];
        }
        if (strcmp(argv[3], "-port") == 0) {
            input_port = atoi(argv[4]);
        }
        else {
            perror("Invalid arguments");
            exit(1);
        }
        // handlzes everything else
    }
    else {
        perror("Invalid arguments");
        exit(1);
    }



    ThreadedServer* s = new ThreadedServer(input_ip, input_port);
    s->waitForConnectionsAndRead();

    sleep(10);
    s->p("closing");
    s->closeSocket();

}