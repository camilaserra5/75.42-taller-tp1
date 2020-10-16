#ifndef RIVEST_H
#define RIVEST_H

void rivest_encode(char *message, int len, const char *key, int offset);

void rivest_decode(char *message, int len, const char *key, int offset);

#endif

