#ifndef CESAR_H
#define CESAR_H

#include <stdio.h>
#include <string.h>

void cesar_encode(char* message, int len, char* key);

void cesar_decode(char* message, int len, char* key);

#endif

