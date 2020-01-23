//Arthur Chu

int main() {
	
	int totalIdleTime[7];
	int minutesIdleTime = 0;
	(int i = 0; i < 7; i++) {
		printf("Please enter today's idle system time, in minutes: \n");
		scanf("%d", &totalIdleTime + i);
		minutesIdleTime += *(totalIdleTime+i);
	}
	printf("Total Idle Time: %d minutes", minutesIdleTime);
	printf("Performance Rate: ");
	printf("Average Daily Idle Time: ");
	printf("The highest system load was on ");
	printf("The lowest system load was on ");
	return 0;
}
