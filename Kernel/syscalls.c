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
void getRTC(timeStruct * time);
void regdump(uint64_t * buffer);
void clearScreen();
void putRectangle(uint32_t hexColor, uint32_t x, uint32_t y, uint32_t base, uint32_t height);
void putCircle(uint32_t hexColor, uint32_t x, uint32_t y, int32_t r);

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
            getRTC((timeStruct *) rdi);
            return;
        case 6:
            regdump((uint64_t *)rdi);
            return;
        case 7:
            _sti();
            beep(rsi,rdi);
            _cli();
            return;
        case 8:
            clearScreen();
            return;
        case 9:
            putRectangle(rdi, rsi, rdx, rcx, r8);
            return;
        case 10:
            putCircle(rdi, rsi, rdx, rcx);
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

void getRTC(timeStruct * time) {
    time->year = getTime(9);
    time->month = getTime(8);
    time->dayOfMonth = getTime(7);
    time->dayOfWeek = getTime(6);
    time->hour = getTime(4);
    time->minute = getTime(2);
    time->second = getTime(0);
}

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


void clearScreen(){
    uint32_t w = getWidth();
    uint32_t h = getHeight();
    for(uint32_t i=0; i < w;i++){
        for(uint32_t j=0;j < h;j++){
            putPixel(0, i,j);
        }
    }
}

void putRectangle(uint32_t hexColor, uint32_t x, uint32_t y, uint32_t base, uint32_t height){
    uint32_t w = getWidth();
    uint32_t h = getHeight();
    if (x + base > w){
        base = w - x;
    }
    if (y + height > h){
        height = h - y;
    }
    for(int dx=0;dx<base;dx++){
        for(int dy=0;dy<height;dy++){
            putPixel(hexColor,dx+x,dy+y);
        }
    }
}

//de https://github.com/mlombardia/arqui_tpe
void putCircle(uint32_t hexColor, uint32_t center_x, uint32_t center_y, int32_t r){
    int x, y;
    for (int i = -r; i <= r; i++) {
        for (int j = -r; j <= r; j++) {
            x = j;
            y = i;
            if ((x*x) + (y*y) < (r*r)) {
                putPixel(hexColor, center_x + x, center_y + y);
            }
        }
    }
    return;
}