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

void intToStringL(uint64_t num, char *string, uint8_t base, uint32_t intLength);
void intToString(uint64_t num, char * string, uint8_t base);
uint32_t uIntLen(uint64_t num, uint8_t base);

void getTime(timeStruct * time);


void fillRegData(uint64_t regData[17]);

void textPosition(uint32_t x, uint32_t y);

void screenInfo(uint32_t * width, uint32_t * height);

void drawScreen(uint32_t x, uint32_t y, uint32_t width, uint32_t height,const char matrix[height][width]);

void getREGS(uint64_t * buffer);

void playSound();

void clearScreen();

void drawRectangle(uint32_t x, uint32_t y, uint32_t base, uint32_t height);

void drawCircle(uint32_t x, uint32_t y, int32_t radius);

void clearRectangle(uint32_t x, uint32_t y, uint32_t base, uint32_t height);

void clearCircle(uint32_t x, uint32_t y, int32_t radius);


void beep(uint8_t frequency, uint64_t ticks);
#endif