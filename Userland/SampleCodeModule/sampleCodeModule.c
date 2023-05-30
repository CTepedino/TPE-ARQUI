#include <libc.h>
#include <stdint.h>
#include <string.h>
#include <libasm.h>

#define READBUF_LENGTH 50
#define COMMANDS_LENGTH 0
#define TIME_LENGTH 8


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

static const char* commands[] = {"time", "dividebyzero", "invalidopcode"}; //Aca van los strings de los nombres de los commandos
static void (*commands_functions[])() = {time, divideByZero, invalidOpCode}; //Aca van las funciones de los comandos

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