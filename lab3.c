// Arthur Chu
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
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
    char* c;
    int file = open(fileName, O_WRONLY|O_CREAT|O_TRUNC, S_IRWXU);
	int p = fork();
    if(p < 0) {
		fprintf(stderr, "You forked up\n");
    } else if (p == 0) {
        char* cString = {"I, the child, am making my mark\n"};
        write(file, cString, strlen(cString));
        exit(0);
    } else {
        char* pString = {"I, the parent, am making a mark\n"};
        write(file, pString, strlen(pString));
    }
    close(file);
}

void forkPrint() {
    int p = fork();
    if(p < 0) {
        fprintf(stderr, "You forked up\n");
    } else if(p == 0) {
        printf("hello\n");
        exit(0);
    } else {
        sleep(1);
        printf("goodbye\n");
    }
}

void forkExec() {
    int p = fork();
    if(p < 0) {
        fprintf(stderr, "You forked up\n");
    } else if( p == 0 ) {
        execl("/bin/ls", "ls", NULL);
        exit(0);
    } else {
    }
}

void twiddle() {
    int status;
    int p = fork();
    if(p < 0) {
        fprintf(stderr, "You forked up\n");
    } else if( p == 0 ) {
        printf("I, the child, am going to twiddle my thumbs for a second\n");
        exit(0);
    } else {
        wait(&status);
        printf("Alright I'm done waiting for the child\n");
    }
}

void twiddlePID() {
    int p = fork();
    int status;
    if (p < 0) {
        fprintf(stderr, "You forked up\n");
    } else if(p == 0) {
        printf("I, the child, am twiddling my thumbs once again\n");
        exit(0);
    } else {
        waitpid(-1 , &status, 0);
        printf("Finally, the child is done\n");
    }
}

void standardOutKill() {
    int p = fork();
    if (p < 0) {
        fprintf(stderr, "You forked up\n");
    } else if(p == 0) {
       close(STDOUT_FILENO);
       printf("Can I, the child, still print?\n"); 
        exit(0);
    } else {
    }
}
int main() {
	//Question 1
	printf("1. Fork\n");
   int x = 100;
	printf("The number of the day is %d, for now. Here comes a family.\n", x);
	birth(&x);
	printf("Someone changed the number of the day to %d!\n", x);
//Both the parent and the child process changed the value of x.
//The final value of x depends only on which process was slower and changed the number last.

	//Question 2
	printf("2. Fork and Open\n");
    forkOpen("temp.txt");
    int tmpFile = open("temp.txt", O_RDWR);
    char tmpString[30];
    printf("temp.txt contents:\n");
    for(int i = 0; i < 2; i++) {
        read(tmpFile, &tmpString, 32);
        printf("%s", tmpString);
    }

	//Question 3
	printf("3. Fork and Printing\n");
    forkPrint();

	//Question 4
	printf("4. Fork and Exec\n");
    forkExec();

	//Question 5
	printf("5. Wait\n");
    twiddle();

	//Question 6
	printf("6. Waitpid\n");
    twiddlePID();

	//Question 7
	printf("7. Standard Out\n");
    standardOutKill();
	return 1;
}

