#include <videoDriver.h>
#include <lib.h>
#define ZERO_EXCEPTION_ID 0x0
#define INVALID_OP_ID 6


extern uint64_t getSampleCodeModuleAddress();
extern uint64_t getStackBase();

static char * regs[] = {"RAX", "RBX", "RCX", "RDX", "RBP","RSI", "RDI", "R8 ", "R9 ", "R10",
                        "R11", "R12", "R13", "R14", "R15", "RSP", "RIP", "RFLAGS"};

static void printERR(const char * message);
static void printREGS(uint64_t * RSP);
static void printREG(char * regName, int nameLen, uint64_t reg, char * buffer);

static void zero_division();
static void invalid_op_code();



void exceptionDispatcher(int exception, uint64_t * RSP) {

	switch (exception){
        case ZERO_EXCEPTION_ID:
            zero_division();
            break;
        case INVALID_OP_ID:
            invalid_op_code();
            break;
        default:
            return;
    }
    printREGS(RSP);
    char rstMsg[] = "Press any key to restart";
    write(2, rstMsg, strlen(rstMsg));
    read(0, rstMsg, 1);

    //TODO: clearScreen

    RSP[15] = getSampleCodeModuleAddress();
    RSP[18] = getStackBase();

}

static void zero_division() {
	printERR("\nERROR: Division by zero is undefined\n");
}

static void invalid_op_code(){
    printERR("\nERROR: Invalid operation code\n");
}

static void printERR(const char * message){
    write(2,message, strlen(message));
}

static void printREGS(uint64_t * RSP) {
    char regBuffer[16];
   //registros generales
   for(int i=0; i<=14;i++){
       printREG(regs[i], 3, RSP[14-i], regBuffer);
   }
   //rsp
   printREG(regs[15], 3, RSP[18], regBuffer);
  /* write(2, regs[15],3);
   write(2, ":    ", 5);
   intToString(RSP[18], regBuffer, 16, 16);
   write(2, regBuffer, 16);
   write(2,"\n",1);*/

   //rip
   printREG(regs[16], 3, RSP[15], regBuffer);
  /* write(2, regs[16], 3);
   write(2, ":    ", 5);
   intToString(RSP[15], regBuffer, 16, 16);
   write(2, regBuffer, 16);
   write(2, "\n", 1);*/

   //rflags
   printREG(regs[17], 6, RSP[17], regBuffer);
  /* write(2, regs[17], 6);
   write(2, ": ", 2);
   intToString(RSP[17], regBuffer, 16, 16);
   write(2, regBuffer, 16);
   write(2, "\n", 1);*/

}


static void printREG(char * regName, int nameLen, uint64_t reg, char * buffer){
    write(2, regName, nameLen);
    write(2, ":     ", 8-nameLen);
    intToString(reg, buffer, 16, 16);
    write(2, buffer, 16);
    write(2, "\n", 1);
}
