#ifndef SOCKET_H
#define SOCKET_H

#include <stdbool.h>
#include <stdio.h>

static const int ERROR_CODE = 1;

typedef struct socket {
    int fd;
    struct addrinfo *info;
} socket_t;

/**
 * Connection is established between the client and the server
 * @param socket
 * @return true if successful
 */
bool socket_accept(socket_t *socket);

/**
 * Binds the socket to the server address
 * @param socket
 * @return true if successful
 */
bool socket_bind(socket_t *socket);

/**
 * Connects the client socket to the server
 * @param socket
 * @return true if successful
 */
bool socket_connect(socket_t *socket);

/**
 * Destroys the socket
 * @param socket
 */
void socket_destroy(socket_t *socket);

/**
 * Creates the socket
 * @param skt
 * @param host
 * @param port
 * @return true if successful
 */
bool socket_init(socket_t *skt, const char *host, const char *port);

/**
 * Puts the server in a passive mode, waiting for the client to make a connection
 * @param socket
 * @return true if successful
 */
bool socket_listen(socket_t *socket);

/**
 * Recieves a buffer from the client
 * @param socket
 * @param buffer
 * @param size
 * @return bytes received
 */
int socket_receive(socket_t *socket, char *buffer, size_t size);

/**
 * Sends the buffer to the client
 * @param socket
 * @param buffer
 * @param size
 * @return bytes sent
 */
int socket_send(socket_t *socket, const char *buffer, size_t size);

#endif
