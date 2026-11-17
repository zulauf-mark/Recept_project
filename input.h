#ifndef INPUT_H
#define INPUT_H

#include <stddef.h>

int input_read_text(const char *prompt, char *buffer, size_t size);
int input_parse_int(const char *text, int *value);
int input_read_int(const char *prompt, int minimum, int maximum, int *value);
int input_read_positive_double(const char *prompt, double *value);
int input_read_yes_no(const char *prompt, char *value);

#endif
