#ifndef VIDEODRIVER_H
#define VIDEODRIVER_H

#include <stdint.h>
#include <font.h>
void putPixel(uint32_t hexColor, uint32_t x, uint32_t y);

void putChar(uint32_t hexColorChar, uint32_t hexColorBG, char c);
void putBackSpace();
void putNewLine();
void scrollUpwards();

int getWidth();
int getHeight();

void setTextPosition(uint32_t x, uint32_t y);
#endif
