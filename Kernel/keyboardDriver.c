#include <keyboardDriver.h>

#define KEYMAP_LEN 85
static char keyboard_map[] = {
    0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t',
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0, 'a', 's',
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v', 'b',
    'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, '7', '8', '9', '-', '4', '5', '6', '+', '1','2','3','0','.','\n'
};
static int keyPressed = 0;
static char buffer;

void keyboard_handler() {
    keyPressed=1;
    buffer = readKey();
}

char getKey() {
    if (keyPressed==0){
        return 0;
    }
    keyPressed=0;
    return buffer<KEYMAP_LEN ? keyboard_map[buffer] : 0;
}


