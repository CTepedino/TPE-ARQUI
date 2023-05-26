include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin
SOURCES=$(wildcard [^_]*.c)
LIBC_C = ../libc.c
LIBC_ASM = ../libc_interrupts.asm
LIBC_ASM_OBJ = ../libc_interrupts.o

all: $(MODULE)

$(MODULE): $(SOURCES) $(LIBC_C) $(LIBC_ASM_OBJ)
	$(GCC) $(GCCFLAGS) -T sampleCodeModule.ld _loader.c $(SOURCES) $(LIBC_C) $(LIBC_ASM_OBJ) -o ../$(MODULE)

$(LIBC_ASM_OBJ): $(LIBC_ASM)
	$(ASM) $(ASMFLAGS) -o $(LIBC_ASM_OBJ) $(LIBC_ASM)

clean:
	rm -rf *.o

.PHONY: all clean print
