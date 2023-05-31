#include <videoDriver.h>
#include <lib.h>
#define ZERO_EXCEPTION_ID 0x0
#define INVALID_OP_ID 6

static char * regs[] = {"RAX", "RBX", "RCX", "RDX", "RSI", "RDI", "R8 ", "R9 ", "R10",
                        "R11", "R12", "R13", "R14", "R15", "RBP", "RSP", "RIP"};

static void printERR(const char * message);
static void printREGS(uint64_t * regStates);

static void zero_division();
static void invalid_op_code();


void exceptionDispatcher(int exception, uint64_t * regStates) {

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
    printREGS(regStates);
    //TODO: reinciar el shell
    while(1);

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

static void printREGS(uint64_t * regStates) {
    char regBuffer[16];
    for (int i = 0; i < 17; i++) {
        write(2, regs[i], strlen(regs[i]));
        write(2, ": ", 2);
        intToString(regStates[i], regBuffer, 16, 16);
        write(2, regBuffer, 16);
        write(2, "\n", 1);
    }

}