#include <string.h>
#include <getopt.h>
#include "common_vigenere.h"
#include "common_cesar.h"
#include "common_rivest.h"

int _get_method_and_key(char **key, char **method, int argc, char **argv) {
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

int _validate_method(const char *method) {
    if ((strncmp(CESAR, method, 5) == 0) ||
        (strncmp(VIGENERE, method, 8) == 0) ||
        (strncmp(RC4, method, 3) == 0)) {
        return 0;
    }
    return 1;
}
