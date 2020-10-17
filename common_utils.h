#ifndef UTILS_H
#define UTILS_H

int get_method_and_key(char **key, char **method, int argc, char **argv);

int validate_method(const char *method);

int validate_port(const char *port);

int validate_key_and_method(const char *key, const char *method);

int validate_parameters(const char *port, const char *key, const char *method);

#endif

