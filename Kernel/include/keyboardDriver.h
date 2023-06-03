#ifndef KEYBOARDDRIVER_H
#define KEYBOARDDRIVER_H

#include <stdint.h>

void keyboard_handler();
char getKey();
void cleanBuffer();
void getAllKeys(char * c);
void getReleasedKeys(char * c);

char readKey();
#endif
