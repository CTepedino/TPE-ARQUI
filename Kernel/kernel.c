#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>

#include <videoDriver.h>
#include <idtLoader.h>
#include <keyboardDriver.h>


extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();


void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{
    void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};
	loadModules(&endOfKernelBinary, moduleAddresses);
	clearBSS(&bss, &endOfKernel - &bss);
    load_idt();
	return getStackBase();
}

//extern scRead(uint64_t fd, char *buffer, uint64_t length);
//extern scWrite(uint64_t fd, char * string, uint64_t count);
int main(){

    ((EntryPoint) sampleCodeModuleAddress)();
   /* char string[60];
    char * buffer = &string[0];
    scRead(0, buffer, 10);
    putString(0xFFFFFF, 0, string);*/ //TODO: esto esta para probar el read, creo que convendria implementar alguna version simplificada del malloc para simplificar las llamadas

	return 0;
}
