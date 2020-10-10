#include<stdlib.h>

void cesar_encode(char* message,  int len, char* key) {
    unsigned char temp;
    for (int i = 0; i < len; i++){
        temp = message[i];
        temp = (temp + atoi(key)) % 256;
        message[i] = temp;
    }
}

void cesar_decode(char* message, int len, char* key) {
    unsigned char temp;
    for (int i = 0; i < len; i++){
        temp = message[i];
        temp = (temp - atoi(key)) % 256;
        message[i] = temp;
    }
}