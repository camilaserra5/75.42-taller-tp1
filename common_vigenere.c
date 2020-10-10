#include <string.h>

void vigenere_encode(char *message, int len, char *key) {
    unsigned char test;
    int keyLen = strlen(key), i, j;
    char newKey[len];
    for (i = 0, j = 0; i < len; ++i, ++j) {
        if (j == keyLen)
            j = 0;
        newKey[i] = key[j];
    }
    newKey[i] = '\0';

    for (i = 0; i < len; ++i) {
        test = message[i];
        test = (test + newKey[i]) % 256;
        message[i] = test;
    }
    message[i] = '\0';
}

void vigenere_decode(char *message, int len, char *key) {
    unsigned char test;
    int keyLen = strlen(key), i, j;
    char newKey[len];
    for (i = 0, j = 0; i < len; ++i, ++j) {
        if (j == keyLen)
            j = 0;
        newKey[i] = key[j];
    }
    newKey[i] = '\0';

    for (i = 0; i < len; ++i) {
        test = message[i];
        test = (test - newKey[i]) % 256;
        message[i] = test;
    }
    message[i] = '\0';
}
