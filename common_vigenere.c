#include <string.h>
#include <stdlib.h>

char* _generate_new_key(int len, const char *key, int offset) {
    int keyLen = strlen(key), i, j;
    char *newKey = malloc(sizeof(char) * (len + 1));
    for (i = 0, j = 0; i < len; ++i, ++j) {
        if (j == keyLen)
            j = 0;
        newKey[i] = key[(j + offset) % keyLen];
    }
    newKey[i] = '\0';
    return newKey;
}

void vigenere_encode(char *message, int len, const char *key, int offset) {
    int i;
    char *newKey = _generate_new_key(len, key, offset);

    for (i = 0; i < len; ++i) {
        message[i] = (message[i] + newKey[i]) % 256;
    }
    message[i] = '\0';
    free(newKey);
}

void vigenere_decode(char *message, int len, const char *key, int offset) {
    int i;
    char *newKey = _generate_new_key(len, key, offset);

    for (i = 0; i < len; ++i) {
        message[i] = (message[i] - newKey[i]) % 256;
    }
    message[i] = '\0';
    free(newKey);
}
