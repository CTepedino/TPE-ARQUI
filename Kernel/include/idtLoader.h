#ifndef IDTLOADER_H
#define IDTLOADER_H

#include <stdint.h>

void setup_IDT_entry (int index, uint64_t offset);
void load_idt();

#endif