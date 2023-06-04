#ifndef KEYBOARDDRIVER_H
#define KEYBOARDDRIVER_H

#include <stdint.h>
#include <defs.h>
#define L_CTRL_SCANCODE 0x1D

void keyboard_handler();
char getKey();
void cleanBuffer();
void getAllKeys(char * c);
void getReleasedKeys(char * c);
int isKeyPress(uint8_t code);

char readKey();
#endif
