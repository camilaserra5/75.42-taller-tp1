#ifndef CESAR_H
#define CESAR_H

#include <stdio.h>
#include <string.h>

void cesar_encode(char *message, int length, const char *key, int offset);

void cesar_decode(char *message, int length, const char *key, int offset);

#endif

