#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <stdint.h>

void sys_read(uint64_t fd, char *buf, uint64_t count);
void sys_write(uint64_t fd, const char *buf, uint64_t count);
void sys_colorWrite(uint64_t charColor, uint64_t bgColor, const char * buf, uint64_t count);
void sys_writeMatrix(uint64_t ** matrix);
void sys_screenInfo(uint32_t * width, uint32_t * height);
void sys_textPosition(uint32_t x, uint32_t y);
void sys_getRTC(uint8_t id, uint32_t * time);


void sys_regData(uint64_t regData[17]);

#endif
