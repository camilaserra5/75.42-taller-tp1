#define _POSIX_C_SOURCE 200112L

#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include "common_socket.h"

bool socket_accept(socket_t *socket) {
    int temp_fd = accept(socket->fd, NULL, NULL);
    if (temp_fd == ERROR_CODE) {
        return false;
    }

    dup2(temp_fd, socket->fd);
    close(socket->fd);
    socket->fd = temp_fd;
    return true;
}

bool socket_bind(socket_t *socket) {
    return bind(socket->fd,
                socket->info->ai_addr,
                socket->info->ai_addrlen) != ERROR_CODE;
}

bool socket_connect(socket_t *socket) {
    return connect(socket->fd,
                   socket->info->ai_addr,
                   socket->info->ai_addrlen) != ERROR_CODE;
}

void socket_destroy(socket_t *socket) {
    freeaddrinfo(socket->info);
    shutdown(socket->fd, SHUT_RDWR);
    close(socket->fd);
}

bool socket_init(socket_t *skt, const char *host, const char *port) {
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if (!host) {
        hints.ai_flags = AI_PASSIVE;
    }

    if (getaddrinfo(host, port, &hints, &skt->info) != 0) {
        return false;
    }
    skt->fd = socket(skt->info->ai_family, skt->info->ai_socktype,
                     skt->info->ai_protocol);
    if (skt->fd == ERROR_CODE) {
        freeaddrinfo(skt->info);
        return false;
    }

    return true;
}

bool socket_listen(socket_t *socket) {
    return listen(socket->fd, 0) != ERROR_CODE;
}

int socket_receive(socket_t *socket, char *buffer, size_t size) {
    int total = 0;
    while (total < size) {
        size_t bytes_written = recv(socket->fd, &buffer[total],
                                    size - total, 0);
        total += bytes_written;
        if (bytes_written == 0) {
            return total;
        }
    }
    return total;
}

int socket_send(socket_t *socket, const char *buffer, size_t size) {
    int total = 0;
    while (total < size) {
        size_t bytes_sent = send(socket->fd, &buffer[total],
                                 size - total, 0);
        total += bytes_sent;
        if (bytes_sent == 0) {
            return total;
        }
    }
    return total;
}


