#ifndef LIB_H
#define LIB_H

#include <stdint.h>

typedef struct timeStruct{
    uint32_t year;
    uint32_t month;
    uint32_t dayOfMonth;
    uint32_t dayOfWeek;
    uint32_t hour;
    uint32_t minute;
    uint32_t second;
} timeStruct;

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);
unsigned long strlen(const char* str);

void intToString(uint64_t n, char * buffer, uint8_t base, uint8_t intLength);

char *cpuVendor(char *result);
uint32_t getTime(int id);
uint64_t * getRegistersData();
#endif