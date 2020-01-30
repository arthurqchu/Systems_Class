//Arthur Chu
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
	
//	int totalIdleTime[7];
//	int minutesIdleTime = 0;
//	for(int i = 0; i < 7; i++) {
//		printf("Please enter today's idle system time, in minutes: \n");
//		scanf("%d", &totalIdleTime[i]);
//		minutesIdleTime += *(totalIdleTime+i);
//	}
	int numDays;
	int i;
	int minutesIdleTime = 0;
	FILE *inputFile;
	if(argc == 1) {
		printf("No input file specified. Run this program with the input file as a command line argument");
	}else if(argc > 1) {
		inputFile = fopen(argv[1], "r");
		fscanf(inputFile, "%d", &numDays);
	}
	
	if(inputFile == NULL) {
		printf("There was an issue opening the file");	
	}
	int totalIdleTime[numDays];
	for(i = 0; i < numDays; i++) {
		int tempDailyMinutes;
		fscanf(inputFile, "%d", &totalIdleTime[i]);
		minutesIdleTime += tempDailyMinutes;
	}

	printf("Total Idle Time: %d minutes\n", minutesIdleTime);	
	float rate = minutesIdleTime / 10080;
	printf("Performance Rate: %.2f%%\n",rate);
	int avgDailyIdleTime = minutesIdleTime / 7;
	printf("Average Daily Idle Time: %d\n", avgDailyIdleTime);

	int maxIdle = 0;
	int minIdle = *totalIdleTime;
	int dayMax = -1;
	int dayMin = 0;
	for(i = 0; i < 7; i++) {
		if(*(totalIdleTime + i) > maxIdle) {
			maxIdle = *(totalIdleTime + i);
			dayMax = i;
		}
		if (*(totalIdleTime + i) < minIdle) {
			minIdle = *(totalIdleTime + i);
			dayMin = i;
		}
	}

	printf("The highest system load was on ");
	if(dayMax == 0) {
		printf("Sunday\n");
	}
	if(dayMax == 1) {
		printf("Monday\n");
	}
	if(dayMax == 2) {
		printf("Tuesday\n");
	}
	if(dayMax == 3) {
		printf("Wednesday\n");
	}
	if(dayMax == 4) {
		printf("Thursday\n");
	}
	if(dayMax == 5) {
		printf("Friday\n");
	}
	if(dayMax == 6) {
		printf("Saturday\n");
	}
	printf("The lowest system load was on ");
	if(dayMin == 0) {
		printf("Sunday\n");
	}
	if(dayMin == 1) {
		printf("Monday\n");
	}
	if(dayMin == 2) {
		printf("Tuesday\n");
	}
	if(dayMin == 3) {
		printf("Wednesday\n");
	}
	if(dayMin == 4) {
		printf("Thursday\n");
	}
	if(dayMin == 5) {
		printf("Friday\n");
	}
	if(dayMin == 6) {
		printf("Saturday\n");
	}
	return 0;
}
