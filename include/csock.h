#ifndef CSOCK_H
#define CSOCK_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define MAX_CLIENT 5 //Max 5 clients
#define PORT    6969

void funerror(const char* errorMsg);

typedef struct client_s{
    char clientName[MAX_CLIENT];
    
}client_s;

#endif