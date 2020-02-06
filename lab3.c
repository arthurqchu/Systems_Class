// Arthur Chu
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

void birth(int* x) {
	int process = fork();
	if(process < 0) {
		//fork didn't fork
		fprintf(stderr, "You forked up\n");
		exit(1);
	} else if (process == 0) {
		//child is born
		printf("Hello I am the child. I like the number 4. Have you seen my parent?\n");
		*x = 4;
        exit(0);
	} else {
		//parent
		printf("Hello I am the parent. I like the number 13. Have you met my child?\n");
		*x = 13;
	}
}

void forkOpen(char* fileName) {
    int file;
    char* c;
    file = open(fileName, O_WRONLY|O_CREAT, S_IRWXU);
	int p = fork();
    if(p < 0) {
		fprintf(stderr, "You forked up\n");
    } else if (p == 0) {
        printf("Child\n");
        char* cString = "I, the child, am a rotten egg\n";
        write(file, cString, strlen(cString));
        exit(0);
    } else {
        printf("Parent\n");
        char* pString = "I, the parent, am a rotten egg\n";
        write(file, pString, strlen(pString));
    }
    close(file);
}
int main() {
	//Question 1
	printf("1. Fork\n");
	int* x;
    *x = 100;
	printf("The number of the day is %d, for now. Here comes a family.\n", *x);
	birth(x);
	printf("Someone changed the number of the day to %d!\n", *x);
//Both the parent and the child process changed the value of x.
//The final value of x depends only on which process was slower and changed the number last.

	//Question 2
	printf("2. Fork and Open\n");
    forkOpen("./temp.txt");
printf("Here");
//    int tmpFile = open("temp.txt", O_RDWR);
//    char* tmpString;
//    read(tmpFile, &tmpString, 30);
//    printf("%s\n", tmpString);

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
