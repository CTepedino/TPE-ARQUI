#include <string.h>
#include <stdint.h>

#define IS_LOWER(c) (c >= 'a' && c <= 'z') ? 1 : 0

int strcmp(const char* str1, const char* str2) {
	while (*str1 == *str2 && *str1 != '\0'){
        str1++;
        str2++;
    }
	return *str1 - *str2;
}

uint64_t strlen(const char* s) {
    int l = 0;
    while (s[l]!= 0){
        l++;
    }
    return l;
}

void intToStringL(uint64_t num, char *string, uint8_t base, uint32_t intLength){
    uint64_t aux;
    string[intLength]=0;
    for(int i=intLength-1; i>=0;i--){
        aux = num%base;
        string[i] = aux<10? '0'+aux : 'A'+aux-10;
        num/=base;
    }
}

void intToString(uint64_t num, char * string, uint8_t base){
    intToStringL(num, string, base, uIntLen(num,base));
}

uint32_t uIntLen(uint64_t num, uint8_t base){
    uint32_t len=1;
    while (num>=base){
        num/=base;
        len++;
    }
    return len;
}

void toUpper(char * buffer,const char * string){
    int i = 0;
    while(string[i]) {
        if (IS_LOWER(string[i])) {
            buffer[i] = string[i] - 0x20;
        }
        else{
            buffer[i]=string[i];
        }
        i++;
    }
    buffer[i]=0;
}