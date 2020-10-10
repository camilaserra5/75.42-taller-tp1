#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include "common_socket.h"
#include "common_protocol.h"
#include "common_cesar.h"
#include "common_rivest.h"
#include "common_vigenere.h"
#define BUFFER_SIZE 64

static const char *ERROR_UNSUPPORTED = "No se reconoce el comando ingresado\n";
static const char *INVALID_USE_CLIENT = "Uso: ./tp client <host> <puerto> --method=<method> --key=<key>\n";

static bool _send_encoded_key(char* key, socket_t socket) {
    protocol_t protocol;
    protocol_init(&protocol, &socket);

    protocol_client_send(&protocol, key, strlen(key));

    protocol_destroy(&protocol);
    return 1;
}

int read_and_send(void (*func)(char *, int, char*), char* key, socket_t socket){
    char buffer[BUFFER_SIZE];
    int read, offset = 0;

    do {
        read = fread(buffer, sizeof(char), BUFFER_SIZE, stdin);
        (*func)(buffer, read, key);
        _send_encoded_key(buffer, socket);
        offset += read;
    } while (read == BUFFER_SIZE);
    return 0;
}

int client(char *host, char *port, char* method, char* key) {
    socket_t socket;
    socket_init(&socket, host, port);
    socket_connect(&socket);

    int res = 1;

    void (*func)(char*, int, char*);

    if (strncmp("cesar", method, 5) == 0) {
        func = &cesar_encode;
    } else if (strncmp("vigenere", method, 8) == 0) {
        func = &cesar_encode;
    } else if (strncmp("rc4", method, 3) == 0) {
        func = &rivest_encode;
    } else {
        printf("%s", ERROR_UNSUPPORTED);
        res = 1;
        return res;
    }

    read_and_send(func, key, socket);

    socket_destroy(&socket);

    return res;
}

int main(int argc, char *argv[]) {
    int res = 1;
    char * separator = "=";

    if (argc < 5) {
        printf("%s", INVALID_USE_CLIENT);
        return 1;
    }

    char* method = strtok(argv[3], separator);
    method = strtok(NULL,separator);

    char* key = strtok(argv[4], separator);
    key = strtok(NULL,separator);

    res = client(argv[1], argv[2], method, key);

    return res;
}
