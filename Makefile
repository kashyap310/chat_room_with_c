# Compiler
CC = gcc

# Directories
INCLUDE_DIR = include
SERVER_DIR = server
CLIENT_DIR = client

# Flags
CFLAGS = -I$(INCLUDE_DIR) -Wall -Wextra

# Output
SERVER_OUTPUT = server.out
CLIENT_OUTPUT = client.out

# Sources
SERVER_SRC = $(SERVER_DIR)/server.c
CLIENT_SRC = $(CLIENT_DIR)/client.c

# Targets
all: server client

server: $(SERVER_SRC)
	$(CC) $(CFLAGS) $(SERVER_SRC) -o $(SERVER_OUTPUT)

client: $(CLIENT_SRC)
	$(CC) $(CFLAGS) $(CLIENT_SRC) -o $(CLIENT_OUTPUT)

# Clean up
clean:
	rm -f $(SERVER_OUTPUT) $(CLIENT_OUTPUT)
