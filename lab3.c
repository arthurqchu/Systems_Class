// Arthur Chu
#include <unistd.h>
#include <stdlib.h>

void birth(int process) {
	process = fork();
	if(process < 0) {
		//fork didn't fork
		fprintf(stderr, "You forked up\n");
		exit(1);
	} else if (process == 0) {
		//child is born
		printf("Hello I have been born. I like the number 4.");
		process = 4;
	} else {
		//parent
		printf("Hello I am the parent. I like the number 13. Have you met my child?");
		process = 13;
	}
}

int main() {
	//Question 1
	printf("1. Fork\n");
	int x = 100;
	printf("The number of the day is 100, for now. Here comes the parent");
	birth(x);
	//Question 2
	printf("2. Fork and Open\n");
	//Question 3
	printf("3. Fork and Printing\n");
	//Question 4
	printf("4. Fork and Exec\n");
	//Question 5
	printf("5. Wait\n");
	//Question 6
	printf("6. Waitpid\n");
	//Question 7
	printf("7. Standard Out\n");

	return 1;
}
