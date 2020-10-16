#define _GNU_SOURCE

#include "common_socket.h"
#include "common_protocol.h"
#include <stdio.h>
#include <string.h>
#include "common_cesar.h"
#include "common_rivest.h"
#include "common_vigenere.h"

#define BUFFER_SIZE 64
static const char *INVALID_USE_SERVER = "Uso: ./tp server <puerto> "
                                        "--method=<method> --key=<key>\n";

static socket_t _get_socket(const char *port) {
    socket_t socket;
    socket_init(&socket, NULL, port);
    socket_bind(&socket);
    socket_listen(&socket);
    socket_accept(&socket);
    return socket;
}

int _server(const char *port, const char *method, const char *key) {
    socket_t socket = _get_socket(port);
    protocol_t protocol;
    protocol_init(&protocol, &socket);

    void (*func)(char *, int, const char *, int);

    if (strncmp(CESAR, method, 5) == 0) {
        func = &cesar_decode;
    } else if (strncmp(VIGENERE, method, 8) == 0) {
        func = &vigenere_decode;
    } else if (strncmp(RC4, method, 3) == 0) {
        func = &rivest_decode;
    } else {
        return 1;
    }

    int cont = BUFFER_SIZE;
    int offset = 0;
    while (cont == BUFFER_SIZE) {
        cont = protocol_server_receive(&protocol, BUFFER_SIZE);
        char *buffer = protocol_get_message(&protocol);
        (*func)(buffer, cont, key, offset);
        printf("%s", buffer);
        offset += cont;
    }

    protocol_destroy(&protocol);
    socket_destroy(&socket);

    return cont;
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("%s", INVALID_USE_SERVER);
        return 0;
    }

    char *separator = "=";

    char *saveptr;
    strtok_r(argv[2], separator, &saveptr);
    char *method = strtok_r(NULL, separator, &saveptr);

    char *saveptrkey;
    strtok_r(argv[3], separator, &saveptrkey);
    char *key = strtok_r(NULL, separator, &saveptrkey);

    _server(argv[1], method, key);

    return 0;
}
