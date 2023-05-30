#include <string.h>
#include <stdint.h>

int strcmp(const char* str1, const char* str2) {
	while (*str1 == *str2 && *str1 != '\0'){
        str1++;
        str2++;
    }
	return *str1 - *str2;
}

uint64_t strlen(const char* s) {
    int l = 0;
    while (*s != 0){
        s++;
        l++;
    }
    return l;
}