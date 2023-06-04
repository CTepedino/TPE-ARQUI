#include <stdint.h>
#include <keyboardDriver.h>
#include <time.h>


void irqDispatcher(uint64_t irq, uint64_t * RSP){
    switch (irq){
        case 0:
            timer_handler();
            break;
        case 1:
            keyboard_handler(RSP);
            break;
    }
}


