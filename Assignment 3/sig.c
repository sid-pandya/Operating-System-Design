#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<time.h>
#include<sys/time.h>

int counter = 0;
clock_t start = 0;
struct timeval begin;

char array[100][100] = {{0}};

void sig_hand(int number)
{
	counter += 10;
	printf("tick %d\n", counter);
	alarm(10);
}

void sig_int(int number)
{
	printf("We got a Signal %s\n", strsignal(number));

	clock_t finish = clock();
	struct timeval end;
	gettimeofday(&end, NULL);
	double interval= (double) (finish - start) / CLOCKS_PER_SEC;

	struct timeval variation = { end.tv_sec - begin.tv_sec, end.tv_usec - begin.tv_usec };
	if(variation.tv_usec < 0) { variation.tv_usec += 1000000; variation.tv_sec -= 1; }

	printf("%15s %s\n", "SystemTime", "UserTime");
	printf("%15f %ld.%06ld\n", interval, variation.tv_sec, variation.tv_usec);
}

void sig_stop(int number)
{
	 printf("Signal %s\n", strsignal(number));
	 int i=0;
	 for(i=0; i< 10; i++)
	 if(strlen(array[i]))
	 printf("%s\n", array[i]);
	 printf("\n");
}

void sig_term(int number)
{
	printf("We got a Signal %s\n", strsignal(number));
	struct timeval end;
	clock_t finish = clock();
	gettimeofday(&end, NULL);
	double interval= (double) (finish - start) / CLOCKS_PER_SEC;
	struct timeval variation = { end.tv_sec - begin.tv_sec, end.tv_usec - begin.tv_usec };
	if(variation.tv_usec < 0) { variation.tv_usec += 1000000; variation.tv_sec -= 1; }
	printf("%15s %s\n", "SystemTime", "UserTime");
	printf("%15f %ld.%06ld\n", interval, variation.tv_sec, variation.tv_usec);
	exit(EXIT_SUCCESS);
} 

int main()
{

	start = clock();
	gettimeofday(&begin, NULL);
	int i, arraycounter = 0;
	char TempString[80]; 
	signal(SIGALRM, sig_hand); 
	signal(SIGINT , sig_int); 
	signal(SIGTERM, sig_term);
	signal(SIGTSTP, sig_stop);
	printf("tick %d\n", counter);
	alarm(10);
 
	while(1)
	{

		 fgets(TempString, 79, stdin);

		if(arraycounter >= 10)
		{
			for(i=1; i< 10; i++)
				strcpy(array[i-1], array[i]);
				arraycounter--;
		}

	strcpy(array[arraycounter], TempString);

	printf("%s\n", array[arraycounter]);

	arraycounter++;
	
	}
	
	return 0;
}
