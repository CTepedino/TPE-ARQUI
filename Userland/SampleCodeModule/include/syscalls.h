#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <stdint.h>

void sys_write(uint64_t fd, const char *buf, uint64_t count);
void sys_read(uint64_t fd, char *buf, uint64_t count);

#endif