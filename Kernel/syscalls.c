#include <stdint.h>
#include <defs.h>
#include <videoDriver.h>
#include <keyboardDriver.h>
#include <lib.h>
#include <interrupts.h>

#define SYSCALL_COUNT 8

extern uint64_t * getREGS();

void read(uint64_t fd, char *buffer, uint64_t length);
void write(uint64_t fd, const char * string, uint64_t count);
void writeMatrix(uint32_t x, uint32_t y, uint32_t width, uint32_t height,const char matrix[height][width]);
void textPosition(uint32_t x, uint32_t y);
void screenInfo(uint32_t * width, uint32_t * height);
void getRTC(uint8_t id, uint32_t * time);
void regdump(uint64_t * buffer);

void syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9, uint64_t rax){
    switch(rax){
        case 0:
            read(rdi, (char*)rsi, rdx);
            return;
        case 1:
            write(rdi, (char*)rsi, rdx);
            return;
        case 2:
            writeMatrix(rdi, rsi, rdx, rcx, r8);
            return;
        case 3:
            screenInfo((uint32_t*)rdi, (uint32_t*)rsi);
            return;
        case 4:
            textPosition(rdi, rsi);
            return;
        case 5:
            getRTC(rdi, (uint32_t*)rsi);
            return;
        case 6:
            regdump((uint64_t *)rdi);
            return;
        case 7:
            //playSound(); ?
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
    uint32_t charColor;
    switch(fd){
        case STDOUT:
            charColor = 0xFFFFFF;
            break;
        case STDERR:
            charColor = 0xFF0000;
            break;
        default:
            return;
    }
    for(int i=0;i<count;i++){
        putChar(charColor, 0, string[i]);
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

void writeMatrix(uint32_t x, uint32_t y, uint32_t width, uint32_t height,const char matrix[height][width]){
    uint32_t h = getHeight();
    uint32_t w = getWidth();
    x = x < w ? x : w;
    y = y < h ? y : h;
    width = width+x < w ? width : w - x;
    height = height + y < h ? height : h - y;
    for(int i=0; i<height;i++){
        for(int j=0; j<width;j++){
            if (matrix[i][j]){
                putPixel(0xFFFFFF,j,i);
            }
            else{
                putPixel(0,j,i);
            }
        }
    }
}


void regdump(uint64_t * buffer){
    uint64_t * aux = getREGS();
    for(int i=0; i<18;i++){
        buffer[i]=aux[i];
    }
}
