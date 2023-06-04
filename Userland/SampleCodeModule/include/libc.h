#ifndef LIBC_H
#define LIBC_H

#include <stdint.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

typedef struct timeStruct{
    uint32_t year;
    uint32_t month;
    uint32_t dayOfMonth;
    uint32_t dayOfWeek;
    uint32_t hour;
    uint32_t minute;
    uint32_t second;
} timeStruct;

void putChar(char c);

void print(const char* string);

char getChar();

void scan(char * buf, uint64_t length);


void getTime(timeStruct * time);


void fillRegData(uint64_t regData[17]);

void textPosition(uint32_t x, uint32_t y);

void screenInfo(uint32_t * width, uint32_t * height);

void getREGS(int * status,uint64_t * buffer);



void clearScreen();

void drawRectangle(uint32_t x, uint32_t y, uint32_t base, uint32_t height);

void drawCircle(uint32_t x, uint32_t y, uint8_t radius);

void clearRectangle(uint32_t x, uint32_t y, uint32_t base, uint32_t height);

void clearCircle(uint32_t x, uint32_t y, uint8_t radius);


void beep(uint8_t frequency, uint64_t ticks);

void getCurrentKeyPress(char * keys);
void getCurrentReleasedKeys(char * rkeys);

void sleep(uint64_t ticks);
#endif