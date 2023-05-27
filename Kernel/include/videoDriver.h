#ifndef VIDEODRIVER_H
#define VIDEODRIVER_H

#include <stdint.h>

void putPixel(uint32_t hexColor, uint32_t x, uint32_t y);
void screenClear();
void putRectangle(uint32_t hexColor, uint32_t bottomX, uint32_t leftY, uint32_t base, uint32_t height);
void putChar(uint32_t hexColorChar, uint32_t hexColorBG, char c);
void putBackSpace();
void putNewLine();
void scrollUpwards();
void putString(uint32_t hexColorChar, uint32_t hexColorBG,const char * string);
int getWidth();
int getHeight();
void putNumberBaseN(uint32_t hexColorChar, uint32_t hexColorBG,unsigned int number,char N);
void putDec(uint32_t hexColorChar, uint32_t hexColorBG,unsigned int dec);
void putHex(uint32_t hexColorChar, uint32_t hexColorBG,unsigned int hex);

#endif
