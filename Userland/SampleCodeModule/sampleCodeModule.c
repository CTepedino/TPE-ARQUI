#include <libc.h>
#include <stdint.h>
#include <string.h>
#include <libasm.h>

#define READBUF_LENGTH 50
#define COMMANDS_LENGTH 5
#define TIME_LENGTH 8

const char* helpstring = "";

static void help(){
	print(helpstring, strlen(helpstring));
}

static const char* registerNames[17] = {
    "RIP", "RAX", "RBX", "RCX", "RDX", "RSI", "RDI", "RBP", "RSP", "R8 ", "R9 ", "R10", "R11", "R12", "R13", "R14", "R15"
};

static void printReg(){
	uint64_t regData[17];
	fillRegData(regData);
	char buf[18];
	for (int i = 0; i < 17; i++) {
		print(registerNames[i], 3);
		print(": ", 2);
		intToString(regData[i], buf);
		print(buf, 18);
		if ((i % 4) == 0)
			print("\n", 1);
		else
			print("   ", 3);
	}
}

static void divideByZero(){
	runDivideByZero();
}

static void invalidOpCode(){
	runInvalidOpCode();
}

static void time(){
	char time[TIME_LENGTH + 1];
	getTime(time);
	print(time,TIME_LENGTH);
	return;
}

static const char* commands[] = {"help", "time", "dividebyzero", "invalidopcode", "printReg"}; //Aca van los strings de los nombres de los commandos
static void (*commands_functions[])() = {help, time, divideByZero, invalidOpCode, printReg}; //Aca van las funciones de los comandos

static int indexCommand(char* readbuf) {
	char *p = readbuf;
	for(int i=0; i<COMMANDS_LENGTH; i++) {
		if(strcmp(p,commands[i]) == 0){
			return i;
		}
	}
	return -1;
}


int main() {
	print("Welcome!\n", 9);

	while(1) {
		print("$ ", 2);
		char command[READBUF_LENGTH] = {0};
		scan(command,READBUF_LENGTH); // No anda porque getChar no anda (Aunque sys_read si anda);

		int index;
		if((index = indexCommand(command))>=0) {
			commands_functions[index]();
		}
		else {
			print(command, strlen(command));
			print(": command not found\n", 20);
		}
	}

	return 0;
}