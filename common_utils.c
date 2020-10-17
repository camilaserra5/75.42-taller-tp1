#include <string.h>
#include <getopt.h>
#include <ctype.h>
#include "common_vigenere.h"
#include "common_cesar.h"
#include "common_rivest.h"

static const char *ERROR_METHOD = "No se reconoce el método ingresado\n";
static const char *ERROR_PORT = "El puerto debe ser numérico\n";
static const char *ERROR_CESAR = "La clave debe ser numérica "
                                 "para el método Cesar\n";


int get_method_and_key(char **key, char **method, int argc, char **argv) {
    static struct option long_options[] = {
            {"method", required_argument, 0, 'm'},
            {"key",    required_argument, 0, 'k'}
    };

    int c;
    while ((c = getopt_long(argc, argv, "m:k:", long_options, NULL)) != -1) {
        if (c == 'm') {
            *method = optarg;
        } else if (c == 'k') {
            *key = optarg;
        }
    }

    if (*key == NULL || *method == NULL) {
        return 1;
    }

    return 0;
}

int validate_method(const char *method) {
    if ((strncmp(CESAR, method, 5) == 0) ||
        (strncmp(VIGENERE, method, 8) == 0) ||
        (strncmp(RC4, method, 3) == 0)) {
        return 0;
    }
    return 1;
}

int _is_numeric(const char *number) {
    for (int i = 0; i < strlen(number); i++) {
        if (!isdigit(number[i])) {
            return 1;
        }
    }
    return 0;
}

int validate_key_and_method(const char *key, const char *method) {
    if ((strncmp(CESAR, method, 5) == 0) && (_is_numeric(key) == 0)) {
        return 0;
    }
    return 1;
}

int validate_port(const char *port) {
    return _is_numeric(port);
}

int validate_parameters(const char *port, const char *key, const char *method) {
    if (validate_method(method)) {
        printf("%s", ERROR_METHOD);
        return 1;
    }

    if (validate_port(port)) {
        printf("%s", ERROR_PORT);
        return 1;
    }

    if (validate_key_and_method(key, method)) {
        printf("%s", ERROR_CESAR);
        return 1;
    }

    return 0;
}
