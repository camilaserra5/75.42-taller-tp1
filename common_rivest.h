#ifndef RIVEST_H
#define RIVEST_H

static const char *RC4 = "rc4";

void rivest_encode(char *message, int length, const char *key, int offset);

void rivest_decode(char *message, int length, const char *key, int offset);

#endif

