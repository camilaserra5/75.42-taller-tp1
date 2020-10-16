#include <string.h>
#include <stdlib.h>

char *_generate_new_key(int length, const char *key, int offset) {
    int keyLength = sizeof(key), i, j;
    char *newKey = malloc(sizeof(char) * (length + 1));
    for (i = 0, j = 0; i < length; ++i, ++j) {
        if (j == keyLength)
            j = 0;
        newKey[i] = key[(j + offset) % keyLength];
    }
    newKey[i] = '\0';
    return newKey;
}

void vigenere_encode(char *message, int length, const char *key, int offset) {
    int i;
    char *newKey = _generate_new_key(length, key, offset);

    for (i = 0; i < length; ++i) {
        message[i] = (message[i] + newKey[i]) % 256;
    }
    message[i] = '\0';
    free(newKey);
}

void vigenere_decode(char *message, int length, const char *key, int offset) {
    int i;
    char *newKey = _generate_new_key(length, key, offset);

    for (i = 0; i < length; ++i) {
        message[i] = (message[i] - newKey[i]) % 256;
    }
    message[i] = '\0';
    free(newKey);
}
