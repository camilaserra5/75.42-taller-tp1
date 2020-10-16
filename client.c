#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include "common_socket.h"
#include "common_protocol.h"
#include "common_cesar.h"
#include "common_rivest.h"
#include "common_vigenere.h"

#define BUFFER_SIZE 64

static const char *ERROR_UNSUPPORTED = "No se reconoce el método ingresado\n";
static const char *INVALID_USE_CLIENT = "Uso: ./tp client <host> <puerto> "
                                        "--method=<method> --key=<key>\n";

void _send_encoded(char *key, int len, socket_t socket) {
    protocol_t protocol;
    protocol_init(&protocol, &socket);

    protocol_client_send(&protocol, key, len);

    protocol_destroy(&protocol);
}

void _read_and_encode(void (*func)(char *, int, const char *, int),
                      const char *key,
                      socket_t socket) {
    char buffer[BUFFER_SIZE];
    int read;
    int offset = 0;

    do {
        read = fread(buffer, sizeof(char), BUFFER_SIZE, stdin);
        (*func)(buffer, read, key, offset);
        _send_encoded(buffer, read, socket);
        offset += read;
    } while (read == BUFFER_SIZE);
}

void _client(const char *host, const char *port, const char *method, const char *key) {
    socket_t socket;
    socket_init(&socket, host, port);
    socket_connect(&socket);

    void (*func)(char *, int, const char *, int);

    if (strncmp(CESAR, method, 5) == 0) {
        func = &cesar_encode;
    } else if (strncmp(VIGENERE, method, 8) == 0) {
        func = &vigenere_encode;
    } else if (strncmp(RC4, method, 3) == 0) {
        func = &rivest_encode;
    } else {
        printf("%s", ERROR_UNSUPPORTED);
        return;
    }

    _read_and_encode(func, key, socket);

    socket_destroy(&socket);
}

int main(int argc, char *argv[]) {
    char *separator = "=";

    if (argc < 5) {
        printf("%s", INVALID_USE_CLIENT);
        return 0;
    }

    char *saveptr_method;
    strtok_r(argv[3], separator, &saveptr_method);
    char *method = strtok_r(NULL, separator, &saveptr_method);

    char *saveptr_key;
    strtok_r(argv[4], separator, &saveptr_key);
    char *key = strtok_r(NULL, separator, &saveptr_key);

    _client(argv[1], argv[2], method, key);

    return 0;
}
