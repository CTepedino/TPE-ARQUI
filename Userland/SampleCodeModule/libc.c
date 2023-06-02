#include <stdint.h>
#include <libc.h>
#include <syscalls.h>
#include <string.h>

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

uint32_t getDay(){
    uint32_t time;
    sys_getRTC(7,&time);
    return time;
}
uint32_t getMonth(){
    uint32_t time;
    sys_getRTC(8,&time);
    return time;
}
uint32_t getHour(){
    uint32_t time;
    sys_getRTC(4,&time);
    return time;
}
uint32_t getMinute(){
    uint32_t time;
    sys_getRTC(2,&time);
    return time;
}