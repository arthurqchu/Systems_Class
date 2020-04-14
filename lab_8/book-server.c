#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

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
	srand(time(NULL));
	while(1) {
		l = sizeof(sin);
		if ((new_s = accept(s, (struct sockaddr *)&sin, &l)) < 0) {
			perror("simplex-talk: accept");
			exit(1);
		}
		while(1){
			len = recv(new_s, buf, sizeof(buf), 0);
			fputs(buf, stdout);
			//Determine what response to send
			int r = (rand() % 2);
			if (buf[(strlen(buf)-2)] == '?'){
				strcpy(buf,"That's an interesting question, but please tell me more about yourself..");
			}else if (r==0) {
				char new_buf[MAX_LINE];
				r = (rand() % 3);
				if (r==0) {
					strcpy(new_buf,"What makes you think ");
					strcat(new_buf, buf);
					strcat(new_buf, "?");
					strcpy(buf,new_buf);
				}else if (r==1) {
					strcpy(new_buf,"How long since ");
					strcat(new_buf, buf);
					strcat(new_buf, " started?");
					strcpy(buf,new_buf);
				}else if (r==2) {
					strcpy(new_buf,"Did you come to me because ");
					strcat(new_buf, buf);
					strcat(new_buf, "?");
					strcpy(buf,new_buf);
				}
			}else {
				r = (rand() % 5);
				if(r==0){
					strcpy(buf,"Tell me more...");
				}else if(r==1){
					strcpy(buf,"I'm sorry to hear that.");
				}else if(r==2){
					strcpy(buf,"How does that make you feel?");
				}else if(r==3){
					strcpy(buf,"Is it really?");
				}else if(r==4){
					strcpy(buf,"Are you sure?");
				}
			}
			fputs(buf,stdout);
			printf("\n");
			//Send the message(buf) back
			buf[MAX_LINE-1] = '\0';
			len = strlen(buf) + 1;
			send(new_s, buf, len, 0);
			//close(new_s);
		}
	}
}
