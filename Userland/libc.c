#include <stdint.h>

extern void putCharHandler(uint64_t fd, const char *buf, uint64_t count);
extern void getCharHandler(uint64_t fd, char *buf, uint64_t count);

void putChar(char c){
    putCharHandler(0,&c,1);
}

void getChar(char *c){
    getCharHandler(0,c,1);
}