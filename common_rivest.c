#include <string.h>

void swap(unsigned char *a, unsigned char *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// key scheduling algorithm
void KSA(const char *key, unsigned char *S) {
    int len = strlen(key);
    for (int i = 0; i < 256; i++)
        S[i] = i;

    int j = 0;
    for (int i = 0; i < 256; i++) {
        j = (j + S[i] + key[(i) % len]) % 256;
        swap(&S[i], &S[j]);
    }
}

// pseudo random generation algorithm
void PRGA(unsigned char *S, char *message, int length, int offset) {
    int i = 0;
    int j = 0;
    for (int n = 0; n < offset; n++) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(&S[i], &S[j]);
    }

    for (int n = 0; n < length; n++) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(&S[i], &S[j]);
        int temp = S[(S[i] + S[j]) % 256];
        message[n] = temp ^ message[n];
    }
}

void rivest_encode(char *message, int length, const char *key, int offset) {
    unsigned char S[256];
    KSA(key, S);
    PRGA(S, message, length, offset);
}

void rivest_decode(char *message, int length, const char *key, int offset) {
    unsigned char S[256];
    KSA(key, S);
    PRGA(S, message, length, offset);
}
