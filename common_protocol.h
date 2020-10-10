#ifndef PROTOCOL_h
#define PROTOCOL_h

#include <stdbool.h>
#include "common_socket.h"

typedef struct protocol {
    socket_t* socket;
    char *message_received;
} protocol_t;

void protocol_init(protocol_t *protocol, socket_t* socket);

int protocol_server_receive(protocol_t *protocol, int length);

int protocol_client_send(protocol_t *protocol, const char *message, int length);

char* protocol_get_message(protocol_t* protocol);

void protocol_destroy(protocol_t *protocol);

#endif
