#include <libc.h>
#include <stdint.h>
#include <string.h>
#include <libasm.h>
#include <pong.h>


#define READBUF_LENGTH 50
#define COMMANDS_LENGTH 6
#define TIME_LENGTH 9

const char* helpstring =
"HELP                 Muestra informacion sobre los distintos programas disponibles.\n"
"TIME                 Imprime en pantalla la hora del sistema.\n"
"DIVIDEBYZERO         Programa que demuestra el funcionamiento de la excepcion \"Divicion por cero\".\n"
"INVALIDOPCODE        Programa que demuestra el funcionamiento de la excepcion \"Codigo de operacion invalido\".\n"
"PRINTREG             Imprime en pantalla informacion sobre todos los registros del procesador.\n"
"PONG                 Abre el juego Pong. El paddle izquierdo se controla con \'W\' y \'S\'.El derecho con \'I\' y \'K\'.\n\n";

static void help(){
	print(helpstring);
}

static char * regNames[] = {"RAX", "RBX", "RCX", "RDX", "RBP","RSI", "RDI", "R8 ", "R9 ", "R10",
                        "R11", "R12", "R13", "R14", "R15", "RSP", "RIP", "RFLAGS"};


static void printSingleReg(char * regName, uint64_t reg, char * buffer){
    uint64_t nameLen = strlen(regName);
    print(regName);
    putChar(':');
    for(int i = 7-nameLen; i>0 ;i--){
        putChar(' ');
    }
    intToStringL(reg, buffer, 16, 16);
    print(buffer);
    putChar('\n');
}

static void printReg(){
	uint64_t regs[18];
    char regBuffer[17];
    getREGS(regs);
    for(int i=0; i<=17;i++) {
        printSingleReg(regNames[i], regs[i], regBuffer);
    }
}



static void divideByZero(){
	runDivideByZero();
}

static void invalidOpCode(){
	runInvalidOpCode();
}

static void time(){
    timeStruct time;
    char buffer[5];
    print("Fecha y hora actual: ");
    getTime(&time);
    intToString(time.dayOfMonth, buffer, 10);
    print(buffer);
    putChar('-');
    intToString(time.month,buffer,10);
    print(buffer);
    putChar('-');
    intToString(time.year, buffer, 10);
    print(buffer);
    putChar(' ');
    time.hour = (time.hour + 21)%24;
   /* if (time.hour < 10){
        putChar('0');
    }*/
    intToStringL(time.hour, buffer, 10, 2);
    print(buffer);
    putChar(':');
   /* if (time.minute < 16){
        putChar('0');
    }*/
    intToStringL(time.minute, buffer, 10, 2);
    print(buffer);
    putChar('\n');
}

static const char* commands[] = {"help", "time", "dividebyzero", "invalidopcode", "printreg", "pong"}; //Aca van los strings de los nombres de los commandos
static void (*commands_functions[])() = {help, time, divideByZero, invalidOpCode, printReg, pong}; //Aca van las funciones de los comandos

static int indexCommand(char* readbuf) {
	char *p = readbuf;
	for(int i=0; i<COMMANDS_LENGTH; i++) {
		if(strcmp(p,commands[i]) == 0){
			return i;
		}
	}
	return -1;
}


static unsigned int scr_width;
static unsigned int scr_height;


int main() {
    screenInfo(&scr_width, &scr_height);
    textPosition(0, scr_height);
    print("Bienvenido!\n\nQue modulo desea correr?\n\n");
	help();
	print("Para correr los modulos, ingrese el comando correspondiente y presione enter.\n\n");

	while(1) {
		print("$ ");
		char command[READBUF_LENGTH] = {0};
		scan(command,READBUF_LENGTH);

		int index;
		if((index = indexCommand(command))>=0) {
			commands_functions[index]();
		}
		else {
			print(command);
			print(": command not found\n");
		}
	}
	return 0;
}