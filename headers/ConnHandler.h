#include "Core.h"

using namespace std;

#ifdef _WIN32
    #define PORT "33471"
#else
    #define PORT "33470"
#endif
#define DOMAIN  AF_INET
#define TRANSPORT SOCK_STREAM
#define PROTOCOL IPPROTO_TCP
#define DNS_DOMAIN "prah.homepc.it"
#include <stdlib.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")

class ConnHandler {
    private:
        int serverSocket;
        //Core core;
        const int MAX_CLIENTS = 10;
        mutex mCore;

        void setupServerSocket();
        void startClientServerComunication();

        int closesocket(int socket) {
                return close(socket);
        }   
    public:
        ConnHandler();
        void clientThread(int clientSocket);

};