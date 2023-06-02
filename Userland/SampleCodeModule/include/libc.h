#ifndef LIBC_H
#define LIBC_H

#include <stdint.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2


void putChar(char c);

void print(const char* string);

char getChar();

void scan(char * buf, uint64_t length);

void intToString(uint64_t num, char * string, uint8_t base);
uint32_t uIntLen(uint64_t num, uint8_t base);

uint32_t getDay();
uint32_t getMonth();
uint32_t getHour();
uint32_t getMinute();


void fillRegData(uint64_t regData[17]);

void textPosition(uint32_t x, uint32_t y);

void screenInfo(uint32_t * width, uint32_t * height);

void drawScreen(uint32_t x, uint32_t y, uint32_t width, uint32_t height,const char matrix[height][width]);

void getREGS(uint64_t * buffer);

#endif