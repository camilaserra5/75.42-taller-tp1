#include <stdlib.h>


void cesar_encode(char *message, int len, const char *key, int offset) {
    for (int i = 0; i < len; i++) {
        message[i] = (message[i] + atoi(key)) % 256;
    }
}

void cesar_decode(char *message, int len, const char *key, int offset) {
    for (int i = 0; i < len; i++) {
        message[i] = (message[i] - atoi(key)) % 256;
    }
}
