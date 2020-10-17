#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include "common_socket.h"
#include "common_protocol.h"
#include "common_cesar.h"
#include "common_rivest.h"
#include "common_vigenere.h"
#include "common_utils.h"

#define BUFFER_SIZE 64

typedef void (*encoder_t)(char *, int, const char *, int);

static const char *INVALID_USE_CLIENT = "Uso: ./tp client <host> <puerto> "
                                        "--method=<method> --key=<key>\n";

void _read_and_encode(encoder_t encoder,
                      const char *key,
                      protocol_t *protocol) {
    char buffer[BUFFER_SIZE];
    int read;
    int offset = 0;

    do {
        read = fread(buffer, sizeof(char), BUFFER_SIZE, stdin);
        (*encoder)(buffer, read, key, offset);
        protocol_client_send(protocol, buffer, read);
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

void _client(const char *host, const char *port,
             const char *method, const char *key) {
    socket_t socket;
    socket_init(&socket, host, port);
    socket_connect(&socket);
    protocol_t protocol;
    protocol_init(&protocol, &socket);

    encoder_t encoder = _get_encoder_function(method);
    _read_and_encode(encoder, key, &protocol);

    protocol_destroy(&protocol);
    socket_destroy(&socket);
}

int main(int argc, char **argv) {
    if (argc < 5) {
        printf("%s", INVALID_USE_CLIENT);
        return 0;
    }

    char *host = argv[1];
    char *port = argv[2];
    char *method = NULL, *key = NULL;
    if (get_method_and_key(&key, &method, argc, argv)) {
        printf("%s", INVALID_USE_CLIENT);
        return 0;
    }

    if (validate_parameters(port, key, method)) {
        return 0;
    }

    _client(host, port, method, key);

    return 0;
}
