# Compiler and flags
CC = gcc
CFLAGS = -Wall -Iinclude
LDFLAGS =

# Directories
OBJDIR = obj
CLIENT_DIR = client_d
SERVER_DIR = server_d

# Source files
CLIENT_SRC = $(CLIENT_DIR)/client.c
SERVER_SRC = $(SERVER_DIR)/server.c
CSOCK_SRC = include/csock.c

# Object files
CLIENT_OBJ = $(OBJDIR)/client.o
SERVER_OBJ = $(OBJDIR)/server.o
CSOCK_OBJ = $(OBJDIR)/csock.o

# Executables
CLIENT_BIN = client
SERVER_BIN = server

# Default target
all: $(CLIENT_BIN) $(SERVER_BIN)

# Ensure the object directory exists
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Build the client executable
$(CLIENT_BIN): $(OBJDIR) $(CLIENT_OBJ) $(CSOCK_OBJ)
	$(CC) $(CFLAGS) -o $@ $(CLIENT_OBJ) $(CSOCK_OBJ) $(LDFLAGS)

# Build the server executable
$(SERVER_BIN): $(OBJDIR) $(SERVER_OBJ) $(CSOCK_OBJ)
	$(CC) $(CFLAGS) -o $@ $(SERVER_OBJ) $(CSOCK_OBJ) $(LDFLAGS)

# Compile client source
$(OBJDIR)/client.o: $(CLIENT_SRC) include/csock.h
	$(CC) $(CFLAGS) -c $(CLIENT_SRC) -o $@

# Compile server source
$(OBJDIR)/server.o: $(SERVER_SRC) include/csock.h
	$(CC) $(CFLAGS) -c $(SERVER_SRC) -o $@

# Compile csock source
$(OBJDIR)/csock.o: $(CSOCK_SRC) include/csock.h
	$(CC) $(CFLAGS) -c $(CSOCK_SRC) -o $@

# Build only the client
client: $(CLIENT_BIN)

# Build only the server
server: $(SERVER_BIN)

# Clean up build artifacts
clean:
	rm -f $(OBJDIR)/*.o $(CLIENT_BIN) $(SERVER_BIN)

.PHONY: all clean client server
