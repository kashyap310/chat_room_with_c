#include "csock.h"
#include <pthread.h>
#include <semaphore.h>

sem_t client_sem;

int main()
{
    int sockFd;
    struct sockaddr_in server_socket, client_socket;
    memset(&server_socket,0,sizeof(struct sockaddr_in));
    memset(&client_socket,0,sizeof(struct sockaddr_in));
    socklen_t client_len = sizeof(client_socket);
    pthread_t client_thread[MAX_CLIENT];
    int i = 0, total_requests = 0;

    // Init semaphore
    sem_init(&client_sem, 0, MAX_CLIENT);

    // setup server socket
    server_socket.sin_family = AF_INET;
    server_socket.sin_addr.s_addr = INADDR_ANY;
    server_socket.sin_port = htons(PORT);

    // Create socket
    sockFd = socket(AF_INET, SOCK_STREAM, 0);
    // Set socket Option
    if (setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
    {
        funerror("setsockopt(SO_REUSEADDR) failed");
    }

    // Bind socket
    if (bind(sockFd, (struct sockaddr *)&server_socket, sizeof(server_socket)) < 0)
    {
        funerror("Bind");
    }
    // listen socket
    if (listen(sockFd, MAX_CLIENT) < 0)
    {
        funerror("Listen");
    }

    while (1)
    {
        sem_wait(&client_sem);
        int *clientFd = malloc(sizeof(int));
        if (clientFd == NULL)
        {
            funerror("malloc");
        }
        *clientFd = accept(sockFd, (struct sockaddr *)&client_socket, &client_len);
        if (*clientFd < 0)
        {
            funerror("Accept");
        }
        total_requests++;
        int value;
        sem_getvalue(&client_sem, &value);
        printf("\n\n[+%d] Connected\n[%d] Sam value\n[%d] count\n", i, value, total_requests);
        if (getpeername(*clientFd, (struct sockaddr *)&client_socket, &client_len) == -1)
        {
            funerror("Get peer name");
        }
        else
        {
            // Get the client's IP address
            char *client_ip = inet_ntoa(client_socket.sin_addr);

            // Get the client's port number
            int client_port = ntohs(client_socket.sin_port);

            printf("Client IP: %s\n", client_ip);
            printf("Client Port: %d\n", client_port);
        }

        if (pthread_create(&client_thread[i], NULL, client_handle, (void *)clientFd) < 0)
        {
            funerror("pthread_Create");
        }
        pthread_detach(client_thread[i]);
        i++;
        i = i % MAX_CLIENT;
    }
    sem_destroy(&client_sem);
    return 0;
}

void *client_handle(void *fd)
{
    int client_fd = *(int *)fd;
    free(fd);

    // Request buffer from server
    char reqbuffer[1024] = {0};
    size_t recvS = recv(client_fd, reqbuffer, 1024, 0);
    reqbuffer[recvS] = '\0';
    requestParms parms = parse(reqbuffer);

    // Print the results
    printf("Request Method: %d\n", parms.reqMethod);
    printf("Request Path: %s\n", parms.path);
    // sleep(10);
    printf("SEM DONE\n");
    sem_post(&client_sem);
    close(client_fd);
    return NULL;
}