#include <lib.h>

uint64_t regs[18] = {0};
static int regsSaved = 0;

void * memset(void * destination, int32_t c, uint64_t length)
{
	uint8_t chr = (uint8_t)c;
	char * dst = (char*)destination;

	while(length--)
		dst[length] = chr;

	return destination;
}

void * memcpy(void * destination, const void * source, uint64_t length)
{
	/*
	* memcpy does not support overlapping buffers, so always do it
	* forwards. (Don't change this without adjusting memmove.)
	*
	* For speedy copying, optimize the common case where both pointers
	* and the length are word-aligned, and copy word-at-a-time instead
	* of byte-at-a-time. Otherwise, copy by bytes.
	*
	* The alignment logic below should be portable. We rely on
	* the compiler to be reasonably intelligent about optimizing
	* the divides and modulos out. Fortunately, it is.
	*/
	uint64_t i;

	if ((uint64_t)destination % sizeof(uint32_t) == 0 &&
		(uint64_t)source % sizeof(uint32_t) == 0 &&
		length % sizeof(uint32_t) == 0)
	{
		uint32_t *d = (uint32_t *) destination;
		const uint32_t *s = (const uint32_t *)source;

		for (i = 0; i < length / sizeof(uint32_t); i++)
			d[i] = s[i];
	}
	else
	{
		uint8_t * d = (uint8_t*)destination;
		const uint8_t * s = (const uint8_t*)source;

		for (i = 0; i < length; i++)
			d[i] = s[i];
	}

	return destination;
}



unsigned long strlen(const char * str){
    int i=0;
    while(str[i]!=0){
        i++;
    }
    return i;
}

void intToString(uint64_t n, char * buffer, uint8_t base, uint8_t intLength) {;
    int aux;
    for(int i=intLength-1; i>=0;i--){
        aux = n%base;
        buffer[i] = aux<10? '0'+aux : 'A'+aux-10;
        n/=base;
    }
}

void saveREGS(uint64_t * RSP){
    regsSaved = 1;
    //generales
    for(int i = 0 ; i<=14 ; i++){
        regs[i] = RSP[14 - i];
    }
    //rsp
    regs[15] = RSP[18];
    //rip
    regs[16] = RSP[15];
    //rflags
    regs[17] = RSP[17];
}

void getREGS(int * status, uint64_t * buffer){
    if (regsSaved) {
        for (int i = 0; i < 18; i++) {
            buffer[i] = regs[i];
        }
    }
    *status = regsSaved;
}

void getRTC(timeStruct * time) {
    time->year = getTime(9);
    time->month = getTime(8);
    time->dayOfMonth = getTime(7);
    time->dayOfWeek = getTime(6);
    time->hour = getTime(4);
    time->minute = getTime(2);
    time->second = getTime(0);
}