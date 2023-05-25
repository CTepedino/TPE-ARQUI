#include <stdint.h>
#include <idtLoader.h>

#define ACS_INT 0x8E

extern void _irq01Handler();
extern void _cli();
extern void _sti();
extern void picMasterMask(uint8_t mask);
extern void picSlaveMask(uint8_t mask);
extern void _syscallHandler();

#pragma pack(push)
#pragma pack (1)

typedef struct {
    uint16_t offset_l;
    uint16_t selector;
    uint8_t cero;
    uint8_t access;
    uint16_t offset_m;
    uint32_t offset_h;
    uint32_t other_cero;
} DESCR_INT;

#pragma pack(pop)

DESCR_INT * idt = (DESCR_INT *) 0;

void setup_IDT_entry (int index, uint64_t offset) {
	idt[index].offset_l = offset & 0xFFFF;
	idt[index].selector = 0x08;
	idt[index].cero = 0;
	idt[index].access = ACS_INT;
	idt[index].offset_m = (offset >> 16) & 0xFFFF;
	idt[index].offset_h = (offset >> 32) & 0xFFFFFFFF;
    idt[index].other_cero = 0;
}

void load_idt() {
    _cli();
    setup_IDT_entry (0x21, (uint64_t) &_irq01Handler);
    setup_IDT_entry (0x80, (uint64_t) &_syscallHandler);
    picMasterMask(0xFD);
    picSlaveMask(0xFF);
    _sti();
}