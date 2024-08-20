#ifndef CSOCK_H
#define CSOCK_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/stat.h>

#define MAX_CLIENT 5 // Max 5 clients
#define PORT 6969
#define SRC_DIR "./src/"
#define MAX_READ_BUFFER 20971520



// Getting Request Type
typedef enum
{
    GET,
    POST,
    INVALID_METHOD
} reqType;

reqType getMethodFromString(const char *type);

typedef struct requestParms
{
    reqType reqMethod;
    char *path;
} requestParms;

requestParms parse(char *request); // parsing request parameters

// Functions error
void funerror(const char *errorMsg);

void *client_handle(void *fd);

// Working with some http helpers

const char *get_filename_ext(const char *filename);
char *get_mime_type(char *filename);

// Threads
void *client_handle(void *arg); //client thread

#endif