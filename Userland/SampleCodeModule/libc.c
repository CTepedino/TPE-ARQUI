#include <stdint.h>
#include <libc.h>
#include <syscalls.h>
#include <string.h>

#define WHITE 0xFFFFFF
#define BLACK 0

void putChar(char c){
    sys_write(STDOUT, &c, 1);
}

void print(const char* string){
    sys_write(STDOUT, string, strlen(string));
}

char getChar(){
    char c;
    sys_read(STDIN,&c,1);
    return c;
}

void textPosition(uint32_t x, uint32_t y){
    sys_textPosition(x,y);
}

void screenInfo(uint32_t * width, uint32_t * height){
    sys_screenInfo(width, height);
}

void scan(char * buf, uint64_t length){
    if (length == 0)
        return;
    
    uint64_t count = 0;
    while (1){
        char c = getChar();
        if (c == '\n'){
            buf[count < (length - 1) ? count : length - 1] = '\0';
            putChar(c);
            return;
        }
        if (c == '\b'){
            if (count > 0){
                count--;
                putChar(c);
            }
        }
        else{
            putChar(c);
            if(count < length - 1)
                buf[count] = c;
            count++;
        }
    }
}

void intToStringL(uint64_t num, char *string, uint8_t base, uint32_t intLength){
    uint64_t aux;
    string[intLength]=0;
    for(int i=intLength-1; i>=0;i--){
        aux = num%base;
        string[i] = aux<10? '0'+aux : 'A'+aux-10;
        num/=base;
    }
}

void intToString(uint64_t num, char * string, uint8_t base){
    intToStringL(num, string, base, uIntLen(num,base));
}

uint32_t uIntLen(uint64_t num, uint8_t base){
    uint32_t len=1;
    while (num>=base){
        num/=base;
        len++;
    }
    return len;
}





void getREGS(uint64_t * buffer){
    sys_regdump(buffer);
}


void drawScreen(uint32_t x, uint32_t y, uint32_t width, uint32_t height,const char matrix[height][width]){
    sys_writeMatrix(x,y,width,height,matrix);
}

void getTime(timeStruct * time){
    sys_getRTC(time);
}

void playSound(){
    sys_playSound();
}

void clearScreen(){
    sys_clear();
}

void drawRectangle(uint32_t x, uint32_t y, uint32_t base, uint32_t height){
    sys_putRectangle(WHITE,x,y,base,height);
}

void drawCircle(uint32_t x, uint32_t y, int32_t radius){
    sys_putCircle(WHITE,x,y,radius);
}

void clearRectangle(uint32_t x, uint32_t y, uint32_t base, uint32_t height){
    sys_putRectangle(BLACK,x,y,base,height);
}

void clearCircle(uint32_t x, uint32_t y, int32_t radius){
    sys_putCircle(BLACK,x,y,radius);
}

void beep(uint8_t frequency, uint64_t ticks){
    sys_beep(frequency, ticks);
}