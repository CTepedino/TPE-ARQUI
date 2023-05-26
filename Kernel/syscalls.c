#include <stdint.h>
#include <keyboardDriver.h>
#include <videoDriver.h>

void read(uint64_t fd, char *buf, uint64_t count){
    if (fd == 0) {
        for (int i = 0; i < count && realKey != '\n'; i++){
            while (!keyPressed);
            if (realKey != '\n') {
                buf[i] = realKey;
            }
            keyPressed = 0;
        }
    }
}

void write(uint64_t fd, const char *buf, uint64_t count){
    if (fd == 0){
        putString(0xFFFFFF, 0, buf);
    }
}