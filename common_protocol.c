#include <stdlib.h>
#include <string.h>
#include "common_protocol.h"
#include "common_socket.h"

void protocol_init(protocol_t *protocol, socket_t *socket) {
    protocol->socket = socket;
    protocol->message_received = NULL;
}

int protocol_server_receive(protocol_t *protocol, int length) {
    if (protocol->message_received != NULL) {
        free(protocol->message_received);
    }
    protocol->message_received = calloc(length + 1, sizeof(char));
    return socket_receive(protocol->socket, protocol->message_received, length);
}

int protocol_client_send(protocol_t *protocol,
                         const char *message,
                         int length) {
    return socket_send(protocol->socket, message, length);
}

char *protocol_get_message(protocol_t *protocol) {
    return protocol->message_received;
}

void protocol_destroy(protocol_t *protocol) {
    free(protocol->message_received);
}
