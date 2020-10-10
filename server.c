#include "common_socket.h"
#include "common_protocol.h"
#include <stdio.h>
#include <string.h>
#include "common_cesar.h"
#include "common_rivest.h"
#include "common_vigenere.h"

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

int server(const char *port, char *method, char *key) {
    socket_t socket = _get_socket(port);
    protocol_t protocol;
    protocol_init(&protocol, &socket);

    void (*func)(char *, int, char *);

    if (strncmp("cesar", method, 5) == 0) {
        func = &cesar_decode;
    } else if (strncmp("vigenere", method, 8) == 0) {
        func = &vigenere_decode;
    } else if (strncmp("rc4", method, 3) == 0) {
        func = &rivest_decode;
    } else {
        return 1;
    }

    int cont = 1;
    while (cont != 0) {
        cont = protocol_server_receive(&protocol, 64);
        char *buffer = protocol_get_message(&protocol);
        (*func)(buffer, strlen(buffer), key);
        printf("%s", buffer);
    }

    protocol_destroy(&protocol);
    socket_destroy(&socket);

    return cont;
}

int main(int argc, char *argv[]) {
    int res = 1;

    if (argc < 4) {
        printf("%s", INVALID_USE_SERVER);
        return 1;
    }
    char *separator = "=";
    char *method = strtok(argv[2], separator);
    method = strtok(NULL, separator);

    char *key = strtok(argv[3], separator);
    key = strtok(NULL, separator);

    res = server(argv[1], method, key);

    return res;
}
