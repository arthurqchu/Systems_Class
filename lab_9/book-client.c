#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define SERVER_PORT 5432
#define MAX_LINE 256

int main(int argc, char * argv[])
{
	FILE *fp;
	struct hostent *hp;
	struct sockaddr_in sin;
	char *host;
	char buf[MAX_LINE];
	int s;
	int len;

	if (argc==2) {
		host = argv[1];
	}
	else {
		fprintf(stderr, "usage: simplex-talk host\n");
		exit(1);
	}

	/* translate host name into peer's IP address */
	hp = gethostbyname(host);
	if (!hp) {
		fprintf(stderr, "simplex-talk: unknown host: %s\n", host);
		exit(1);
	}

	/* build address data structure */
	memset((char *)&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	memcpy((char *)&sin.sin_addr, hp->h_addr, hp->h_length);
	sin.sin_port = htons(SERVER_PORT);

	/* active open */
	if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("simplex-talk: socket");
		exit(1);
	}
	if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0)
	{
		perror("simplex-talk: connect");
		close(s);
		exit(1);
	}
	/* main loop: get and send lines of text */
  printf("Send a message to the server: ");
	while (fgets(buf, sizeof(buf), stdin)) {	
		//Edit the message in buf to contain the check value
		//Check value will be summation of bits of message
		//First sum the bits while building a new string that contains the bits from input
		int checkSum = 0;
		int origMessageLength = 0;
		char result[MAX_LINE] = "";
		for (int i = 0; i < strlen(buf); i++) {
			if (buf[i] == '1') {
				checkSum += 1;
				origMessageLength +=1;
				strncat(result,"1",1);
			} else if (buf[i] == '0') {
				origMessageLength +=1;
				strncat(result,"0",1);
			}
		}

		//Turn checkSum into string, add it to the end of result, use '.' as delimiter
		char checkSumString[strlen(result)];
		sprintf(checkSumString,".%d\n", checkSum);
		strcat(result, checkSumString);

		//Introduce a random error
		srand(time(NULL));
		int r = rand() % 10;
		if (r == 0 || r == 1 || r== 2) {
			r = rand() % (origMessageLength -1);
			if (result[r] == '1') {result[r] = '0';}
			else if(result[r] == '0') {result[r] = '1';}
			printf("Looks like there's been a flip. Data sent: %s", result);
		}

		len = strlen(result) + 1;
		send(s, result, len, 0);
    printf("Send a message to the server: ");
	}
}

