#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define SERVER_PORT 5432
#define MAX_PENDING 1
#define MAX_LINE 256

int main()
{
	struct sockaddr_in sin;
	char buf[MAX_LINE];
	int len;
  unsigned int l;
	int s, new_s;

	/* build address data structure */
	memset((char *)&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(SERVER_PORT);

	/* setup passive open */
	if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("simplex-talk: socket");
		exit(1);
	}
	if ((bind(s, (struct sockaddr *)&sin, sizeof(sin))) < 0) {
		perror("simplex-talk: bind");
		exit(1);
	}
	listen(s, MAX_PENDING);

	/* wait for connection, then receive and print text */
	while(1) {
		l = sizeof(sin);
		if ((new_s = accept(s, (struct sockaddr *)&sin, &l)) < 0) {
			perror("simplex-talk: accept");
			exit(1);
		}
		while ((len = recv(new_s, buf, sizeof(buf), 0))) {
			//Take the incoming string and isolate the data and checksum
			char data[MAX_LINE];
			char checksumString[MAX_LINE];

			char* token = strtok(buf, ".");
			strcpy(data, token);
			token = strtok(NULL, ".");
			strcpy(checksumString, token);
			printf("Data: %s\n", data);
			printf("Checksum: %s\n", checksumString);
			//change checksum from string to int
			int checksumInt = atoi(checksumString);
			printf("Checksum from string to int: %d\n", checksumInt);

			//Sum the data and compare to checksum
			int dataSum = 0;
			for (int i = 0; i < strlen(data); i++) {
				if (data[i] == '1') {dataSum += 1;}
			}
			if (dataSum == checksumInt) {
				printf("No discrepancies between the data and checksum were detected\n");
			} else {printf("Error: A discrepancy between the data and the checksum was found\n");}
			//fputs(buf, stdout);
			}
		close(new_s);
	}
}
