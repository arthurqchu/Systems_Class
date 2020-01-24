//Arthur Chu
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
bool isHex(char* string) {
	char* ch = string; 
	for(int i = 0; i < strlen(string); i++) {
		if(*ch < 48) {
			return false;
		}
		if(*ch > 58 && *ch < 65) {
			return false;
		}
		if(*ch > 70 && *ch < 97) {
			return false;
		}
		if(*ch > 102) {
			return false;
		}
	}
	return true;
}

int main(void) {
	bool done = false;
	while(done == false) {
		printf("Please enter a hexadecimal number: \n");
		char input[20];
		scanf("%s", input);
		if(isHex(input) == true) {
			printf("Thank you!\n");
			done = true;
		}
	}
	return 0;
}
