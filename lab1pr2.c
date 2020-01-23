//Arthur Chu
#include <stdio.h>
#include <stdbool.h>
bool isHex(char* string) {
	char* ch; 
	while(*ch != '\0') {
		ch = string;
		if(*ch >= '0' && *ch <= '9') {
			ch++;
		}
		if(*ch >= 'A' && *ch <= 'F') {
			ch++;
		}
		else {
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
			printf("Thank you!");
			done = true;
		}
	}
}
