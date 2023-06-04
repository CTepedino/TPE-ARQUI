#ifndef STRING_H
#define STRING_H

#include <stdint.h>

int strcmp(const char* str1, const char* str2);

uint64_t strlen(const char* s);

void intToStringL(uint64_t num, char *string, uint8_t base, uint32_t intLength);

void intToString(uint64_t num, char * string, uint8_t base);

uint32_t uIntLen(uint64_t num, uint8_t base);

#endif