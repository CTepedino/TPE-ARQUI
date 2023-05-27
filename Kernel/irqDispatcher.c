#include <stdint.h>
#include <keyboardDriver.h>

void int_20(){
    return; //TODO: timer_handler?
}

void int_21(){
    keyboard_handler();
}

void irqDispatcher(uint64_t irq){
    void (*functPointer[])() = {int_20, int_21};
    functPointer[irq]();
}