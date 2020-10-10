#ifndef SOCKET_H
#define SOCKET_H

#include <stdbool.h>
#include <stdio.h>

static const int ERROR_CODE = 1;

typedef struct socket {
    int fd;
    struct addrinfo *info;
} socket_t;

bool socket_accept(socket_t *socket);

bool socket_bind(socket_t *socket);

bool socket_connect(socket_t *socket);

void socket_destroy(socket_t *socket);

bool socket_init(socket_t *skt, const char *host, const char *port);

bool socket_listen(socket_t *socket);

int socket_receive(socket_t *socket, char *buffer, size_t size);

int socket_send(socket_t *socket, const char *buffer, size_t size);

#endif
