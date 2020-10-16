#ifndef VIGENERE_H
#define VIGENERE_H

void vigenere_encode(char *message, int length, const char *key, int offset);

void vigenere_decode(char *message, int length, const char *key, int offset);

#endif

