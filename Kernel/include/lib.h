#ifndef LIB_H
#define LIB_H

#include <stdint.h>

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);
unsigned long strlen(const char* str);

void intToString(uint64_t n, char * buffer, uint8_t base, uint8_t intLength);

char *cpuVendor(char *result);
char getTime(int id);
uint64_t * getREGS();
#endif