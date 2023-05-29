#include <libc.h>
#include <stdint.h>
#include <string.h>

#define READBUF_LENGTH 50
#define MAX_PARAMETERS 3
#define LENGTH_PARAMETERS 25

static const char* commands[] = {}; //Aca van los strings de los nombres de los commandos
static void (*commands_functions[])(char parameters[MAX_PARAMETERS][LENGTH_PARAMETERS]) = {}; //Aca van las funciones de los comandos

#define COMMANDS_LENGTH (sizeof(commands)/sizeof(commands[0]))

static int indexCommand(char* readbuf) {
	char *p = readbuf;
	for(int i=0; i<COMMANDS_LENGTH; i++) {
		if(strcmp(p,commands[i]) == 0){
			return i;
		}
	}
	return -1;
}

void getCommand(char command[READBUF_LENGTH], char parameters[MAX_PARAMETERS][LENGTH_PARAMETERS], char readbuf[READBUF_LENGTH]) {
	int i, j, k;
	
	for(i=0, j=0; i<READBUF_LENGTH && readbuf[i]!=' '; i++){
			command[j++] = readbuf[i];
	}

	command[j] = 0;

	while(i<READBUF_LENGTH && readbuf[i]==' '){
		i++;
	}

	for(j=0, k=0; i<READBUF_LENGTH;) {
		if(k>=MAX_PARAMETERS || j>=LENGTH_PARAMETERS)
			return;
		if(readbuf[i]!=' ') {
			parameters[k][j++] = readbuf[i++];
		}
		else {
			parameters[k][j] = 0;
			k++;
			j=0;
			while(i<READBUF_LENGTH && readbuf[i]==' '){
				i++;
			}
		}
	}
}


int main() {
	print("Welcome!\n", 9);

	while(1) {
		print("$ ", 2);
		char readbuf[READBUF_LENGTH] = {0};
		scan(readbuf,READBUF_LENGTH); // No anda porque getChar no anda (Aunque sys_read si anda)

		char command[READBUF_LENGTH] = {0};
		char parameters[MAX_PARAMETERS][LENGTH_PARAMETERS] = {{0}};
		getCommand(command, parameters, readbuf);

		int index;
		if((index = indexCommand(command))>=0) {
			commands_functions[index](parameters);
		}
		else {
			print(command, strlen(command));
			print(": command not found\n", 20);
		}
	}

	return 0;
}