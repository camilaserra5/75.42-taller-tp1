#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include "client.h"
#include "common_utils.h"

static const char *INVALID_USE_CLIENT = "Uso: ./tp client <host> <puerto> "
                                        "--method=<method> --key=<key>\n";

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

    client(host, port, method, key);

    return 0;
}
