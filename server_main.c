#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include "server.h"
#include "common_utils.h"

#define BUFFER_SIZE 64
static const char *INVALID_USE_SERVER = "Uso: ./tp server <puerto> "
                                        "--method=<method> --key=<key>\n";

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

    server(port, method, key);

    return 0;
}
