#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include "common_socket.h"
#include "common_cesar.h"
#include "common_rivest.h"
#include "common_vigenere.h"

#define BUFFER_SIZE 64

typedef void (*encoder_t)(char *, int, const char *, int);

void _read_and_encode(encoder_t encoder,
                      const char *key,
                      socket_t *socket) {
    char buffer[BUFFER_SIZE];
    int read;
    int offset = 0;

    do {
        read = fread(buffer, sizeof(char), BUFFER_SIZE, stdin);
        (*encoder)(buffer, read, key, offset);
        socket_send(socket, buffer, read);
        offset += read;
    } while (read == BUFFER_SIZE);
}

encoder_t _get_encoder_function(const char *method) {
    encoder_t encoder = NULL;
    if (strncmp(CESAR, method, 5) == 0) {
        encoder = &cesar_encode;
    } else if (strncmp(VIGENERE, method, 8) == 0) {
        encoder = &vigenere_encode;
    } else if (strncmp(RC4, method, 3) == 0) {
        encoder = &rivest_encode;
    }
    return encoder;
}

void client(const char *host, const char *port,
             const char *method, const char *key) {
    socket_t socket;
    socket_init(&socket, host, port);
    socket_connect(&socket);

    encoder_t encoder = _get_encoder_function(method);
    _read_and_encode(encoder, key, &socket);

    socket_destroy(&socket);
}