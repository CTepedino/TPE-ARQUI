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