#include <stdlib.h>

void cesar_encode(char *message, int len, char *key) {
    for (int i = 0; i < len; i++) {
        unsigned char temp;
        temp = message[i];
        temp = (temp + atoi(key)) % 256;
        message[i] = temp;
    }
}

void cesar_decode(char *message, int len, char *key) {
    for (int i = 0; i < len; i++) {
        unsigned char temp;
        temp = message[i];
        temp = (temp - atoi(key)) % 256;
        message[i] = temp;
    }
}
