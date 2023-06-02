#include <stdint.h>
#include <keyboardDriver.h>


void int_21(){
    keyboard_handler();
}

void irqDispatcher(uint64_t irq){
    switch (irq){
        case 1:
            int_21();
            break;
    }
}