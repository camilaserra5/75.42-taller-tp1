#ifndef RIVEST_H
#define RIVEST_H

void rivest_encode(char *message, int len, char *key, int offset);

void rivest_decode(char *message, int len, char *key, int offset);

#endif

