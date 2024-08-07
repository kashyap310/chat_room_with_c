//
// Created by kali on 8/4/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>


#define MAX_LINE 100
// socket
// connect
// read/write

void p_error(const char *error);

int main() {
    char buffer[1024];
    char input[MAX_LINE];
    const char *exit_cond = "exit";
    struct sockaddr_in serverAddr;

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5000);

    if (inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) <= 0) {
        printf("Invalid address/ Address not supported \n");
        return -1;
    }

    int clientFD = socket(AF_INET, SOCK_STREAM, 0);
    if (clientFD < 0) {
        p_error("ClientFD");
    }

    int status = connect(clientFD, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    if (status < 0) {
        p_error("Connect");
    }

    printf("Enter Message\n");
    while(1) {

        fgets(input, sizeof(input),stdin);
        size_t len = strlen(input);
        printf("%d\n",len);
        if(len==1){input[len-1]='\n';   }
        if(len!=0) {
            input[len-1]='\0';
        }

        if(strcmp(input,exit_cond)==0) {
            printf("Bye;");
            break;
        }

        send(clientFD, input, strlen(input), 0);
        ssize_t valueread = read(clientFD, buffer, sizeof(buffer) - 1);
        if (valueread < 0) {
            p_error("Read");
        }
        buffer[valueread] = '\0'; // Null-terminate the buffer

        printf("Server: %s\n", buffer);
    }

    close(clientFD);
    return 0;
}

void p_error(const char *error) {
    perror(error);
    exit(EXIT_FAILURE);
}
