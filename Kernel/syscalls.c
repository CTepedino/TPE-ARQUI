#include <stdint.h>
#include <defs.h>
#include <videoDriver.h>
#include <keyboardDriver.h>
#include <lib.h>
#include <interrupts.h>

#define SYSCALL_COUNT 7

void read(uint64_t fd, char *buffer, uint64_t length);
void write(uint64_t fd, const char * string, uint64_t count);
void colorWrite(uint64_t charColor,uint64_t bgColor, const char * string, uint64_t count);
void writeMatrix(const uint64_t ** matrix);
void textPosition(uint32_t x, uint32_t y);
void screenInfo(uint32_t * width, uint32_t * height);
void getRTC(uint8_t id, uint32_t * time);


void syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9, uint64_t rax){
    switch(rax){
        case 0:
            read(rdi, (char*)rsi, rdx);
            return;
        case 1:
            write(rdi, (char*)rsi, rdx);
            return;
        case 2:
            colorWrite(rdi, rsi, (char*)rdx, rcx);
            return;
        case 3:
            writeMatrix((const uint64_t**)rdi);
            return;
        case 4:
            screenInfo((uint32_t*)rdi, (uint32_t*)rsi);
            return;
        case 5:
            textPosition(rdi, rsi);
            return;
        case 6:
            getRTC(rdi, (uint32_t*)rsi);
            return;
        case 7:
           // getREGS()
            return;
    }
}

void read(uint64_t fd, char *buffer, uint64_t length){
   // getKey(); //para consumir el input en caso de que se haya apretado el teclado antes
    if (fd==STDIN){
        _sti();
        for(int i=0;i<length;i++){
            do {
                buffer[i]=getKey();
            } while(buffer[i]==0);
        }
        _cli();
    }
}
void write(uint64_t fd, const char * string, uint64_t count){
    switch(fd){
        case STDOUT:
            colorWrite(0xFFFFFF, 0, string, count);
            return;
        case STDERR:
            colorWrite(0xFF0000, 0, string, count);
            return;
    }
}

void textPosition(uint32_t x, uint32_t y){
    setTextPosition(x,y);
}

void screenInfo(uint32_t * width, uint32_t * height){
    *height = getHeight();
    *width  = getWidth();
}

void getRTC(uint8_t id, uint32_t * time) {
    if (id <= 9){
    *time = getTime(id);
    }
}//id: 0 -> secs, 2 -> mins, 4 -> hrs, 6-> diaSem, 7 -> diaMes, 8 -> mes, 9-> year. 1, 3 y 5 son alarmas. 0xA en adelante no necesitamos

void colorWrite(uint64_t charColor, uint64_t bgColor, const char * string, uint64_t count){
    for(int i =0; i<count; i++){
        putChar(charColor, bgColor, string[i]);
    }
}

void writeMatrix(const uint64_t **matrix){
    uint64_t h = getHeight();
    uint64_t w = getWidth();
    for(int j=0; j<h; j++){
        for (int i=0; i<w ; i++) {
            putPixel(matrix[i][j],i, j);
        }
    }
}

