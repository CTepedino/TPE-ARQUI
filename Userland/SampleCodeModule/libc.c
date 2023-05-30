#include <stdint.h>
#include <libc.h>
#include <syscalls.h>

void putChar(char c){
    print(&c, 1);
}

void print(const char* buf, uint64_t count){
    sys_write(STDOUT, buf, count);
}

char getChar(){
    char c;
    sys_read(STDIN,&c,1);
    return c;
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
        if (c == '\b')
            count--;
        else{
            putChar(c);
            if(count < length - 1)
                buf[count] = c;
            count++;
        }
    }
}

void intToString(uint64_t num, char * str) {
    int i = 0;
    while (num > 0){
        str[i++] = num % 10 + '0';
        num /= 10;
    }

    str[i] = 0;
    
    int length = i;
    for (int j = 0; j < length / 2; j++) {
        char temp = str[j];
        str[j] = str[length - j - 1];
        str[length - j - 1] = temp;
    }
}

void getTime(char * buf){
    char * p = buf;
    uint64_t time = sys_time();

    intToString((time & 0xFF), p);
    p[2] = ':';
    intToString((time >> 8) & 0xFF, p);
    p[5] = ':';
    intToString((time >> 16) & 0xFF, p);
    p[8] = 0;
}