#ifndef STRINGS_H
#define STRINGS_H

#include <stdint.h>
#include <stddef.h>

int strcmp(const char *s1, const char *s2);
void uint8_to_string(uint8_t num, char* str);
char* strcpy(char* dest, const char* src);
char* strncpy(char* dest, const char* src, size_t n);

#endif