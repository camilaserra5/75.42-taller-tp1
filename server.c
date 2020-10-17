#define _GNU_SOURCE

#include "common_socket.h"
#include "common_protocol.h"
#include <stdio.h>
#include <string.h>
#include "common_cesar.h"
#include "common_rivest.h"
#include "common_vigenere.h"
#include "common_utils.h"

#define BUFFER_SIZE 64
static const char *INVALID_USE_SERVER = "Uso: ./tp server <puerto> "
                                        "--method=<method> --key=<key>\n";

typedef void (*decoder_t)(char *, int, const char *, int);

static socket_t _get_socket(const char *port) {
    socket_t socket;
    socket_init(&socket, NULL, port);
    socket_bind(&socket);
    socket_listen(&socket);
    socket_accept(&socket);
    return socket;
}

void _read_and_decode(protocol_t *protocol,
                      const char *key,
                      decoder_t decoder) {
    int cont = BUFFER_SIZE;
    int offset = 0;
    while (cont == BUFFER_SIZE) {
        cont = protocol_server_receive(protocol, BUFFER_SIZE);
        char *buffer = protocol_get_message(protocol);
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

void _server(const char *port, const char *method, const char *key) {
    socket_t socket = _get_socket(port);
    protocol_t protocol;
    protocol_init(&protocol, &socket);

    decoder_t decoder = _get_decoder_function(method);
    _read_and_decode(&protocol, key, decoder);

    protocol_destroy(&protocol);
    socket_destroy(&socket);
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("%s", INVALID_USE_SERVER);
        return 0;
    }

    char *port = argv[1];
    char *method = NULL, *key = NULL;
    if (get_method_and_key(&key, &method, argc, argv)) {
        printf("%s", INVALID_USE_SERVER);
        return 0;
    }

    if (validate_parameters(port, key, method)) {
        return 0;
    }

    _server(port, method, key);

    return 0;
}
