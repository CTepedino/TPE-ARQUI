#ifndef LIBC_H
#define LIBC_H

#include <stdint.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

void putChar(char c);

void print(const char* buf, uint64_t count);

char getChar();

void scan(char * buf, uint64_t length);

void intToString(uint64_t num, char * string);

void getTime(char * buf);

void fillRegData(uint64_t regData[17]);

#endif