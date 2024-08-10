#include "csock.h"
#include<pthread.h>

int main(){
    int sockFd, clinetFD[MAX_CLIENT];    
    struct sockaddr_in server_socket,client_socket;
    pthread_t client_thread[MAX_CLIENT];

    // setup server socket
    server_socket.

    if (setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
    {
        funerror("setsockopt(SO_REUSEADDR) failed");
    }

    return 0;
}

