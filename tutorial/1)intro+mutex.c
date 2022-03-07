
#include "../includes/philosophers.h"
#include <pthread.h>

pthread_mutex_t mutex;
int mails = 0;

void*   routine()
{
	printf("Test from threads\n");
	sleep(3);// without sleep, insta start-end/start-end, with sleep start start end end
	printf("Ending thread\n");

	int i = 10000000;
	while (i--)
	{
		pthread_mutex_lock(&mutex);		//like this mails: 20M, commenting lock/unlock mails : 10 M
		mails++;
		pthread_mutex_unlock(&mutex);
	}
	
}

int main (void)
{
	pthread_t t1, t2;
	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return 1;
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return 2;
	if (pthread_join(t1, NULL) != 0)
		return 3;
	if (pthread_join(t2, NULL) != 0)
		return 4;

	pthread_mutex_destroy(&mutex);

	printf("\nmails: %i\n", mails);










	/*
	struct timeval curren_time;
	gettimeofday(&curren_time, NULL);
	printf("seconds: %ld\n, microsecond: %ld\n", curren_time.tv_sec, curren_time.tv_usec);
	

	
	return (0);
}