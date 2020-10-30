#define _GNU_SOURCE

#include "common_socket.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common_cesar.h"
#include "common_rivest.h"
#include "common_vigenere.h"

#define BUFFER_SIZE 64

typedef void (*decoder_t)(char *, int, const char *, int);

static socket_t _get_socket(const char *port) {
    socket_t socket;
    socket_init(&socket, NULL, port);
    socket_bind(&socket);
    socket_listen(&socket);
    socket_accept(&socket);
    return socket;
}

void _read_and_decode(socket_t *socket,
                      const char *key,
                      decoder_t decoder) {
    int cont = BUFFER_SIZE;
    int offset = 0;
    char* buffer = NULL;
    while (cont == BUFFER_SIZE) {
        if (buffer != NULL) {
            free(buffer);
        }
        buffer = calloc(BUFFER_SIZE + 1, sizeof(char));
        cont = socket_receive(socket, buffer, BUFFER_SIZE);
        (*decoder)(buffer, cont, key, offset);
        printf("%s", buffer);
        offset += cont;
    }
}

decoder_t _get_decoder_function(const char *method) {
    decoder_t decoder = NULL;
    if (strncmp(CESAR, method, 5) == 0) {
        decoder = &cesar_decode;
    } else if (strncmp(VIGENERE, method, 8) == 0) {
        decoder = &vigenere_decode;
    } else if (strncmp(RC4, method, 3) == 0) {
        decoder = &rivest_decode;
    }
    return decoder;
}

void server(const char *port, const char *method, const char *key) {
    socket_t socket = _get_socket(port);

    decoder_t decoder = _get_decoder_function(method);
    _read_and_decode(&socket, key, decoder);

    socket_destroy(&socket);
}