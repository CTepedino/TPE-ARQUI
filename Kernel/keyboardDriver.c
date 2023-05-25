#include <stdio.h>
#include <videoDriver.h>

extern char readKey();

char keyboard_map[128] = {
    '\0', '\0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t',
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', '\0', 'a', 's',
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', '\0', '\\', 'z', 'x', 'c', 'v', 'b',
    'n', 'm', ',', '.', '/', '\0', '*', '\0', ' ', '\0'
};



void keyboard_handler(){
    char key = readKey();
    if(key >= 0 && key < 128){
        putChar(0xFFFFFF, 0, keyboard_map[key]);
    }
}