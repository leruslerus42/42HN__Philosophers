
#include "../includes/philosophers.h"
#include <pthread.h>

//ARGS: number of philos/ time to die/ time to eat/ time to sleep/ [number of tries each OHILO must eat, fakultativ]

pthread_mutex_t mutex;
int mails = 0;

void*   routine()
{
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
    pthread_t th[4];
    pthread_mutex_init(&mutex, NULL);

    int i = 0;
    while (i < 4)
    {
        if (pthread_create(th + i, NULL, &routine, NULL) != 0)
        {
            perror("Error in thread's creation!\n");
            return 1;
        }
        printf("Thread %i has started\n",i);
		i++;
    }
    i = 0;
	while (i < 4)
    {
        if (pthread_join(th[i], NULL) != 0)
            return 2;
        printf("Thread %i has finished\n",i);
		i++;
    }

    pthread_mutex_destroy(&mutex);

    printf("\nmails: %i\n", mails);









    /*
    struct timeval curren_time;
    gettimeofday(&curren_time, NULL);
    printf("seconds: %ld\n, microsecond: %ld\n", curren_time.tv_sec, curren_time.tv_usec);
    */

    
    return (0);
}