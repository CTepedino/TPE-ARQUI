#include <stdint.h>
#include <defs.h>
#include <videoDriver.h>
#include <keyboardDriver.h>
#include <lib.h>


void read(uint64_t fd, char *buffer, uint64_t length);
void write(uint64_t fd, const char * string, uint64_t count);
static void writeMatrix();
static void getRTC();

//TODO: el switch es provisorio, despues lo cambio a un array
void syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9, uint64_t rax){
    switch(rax){
        case 0:
            read(rdi, (char *) rsi, rdx);
            return;
        case 1:
            write(rdi, (char *) rsi, rdx);
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
    uint64_t charColor;
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
    for (int i=0; i<count ; i++){
        putChar(charColor, 0, string[i]);
    }
}

