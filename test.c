#include <stdio.h>
#include <pthread.h>

void 	addInt()
{
	double i = 0;
	while (i < 9348583245424)
	{
		i+=1;
	}
	printf("%f\n", i);
}


int main()
{
	pthread_t thread;
	pthread_t thread2;
	pthread_create(&thread2, NULL, (void*)addInt, NULL);
	pthread_create(&thread, NULL, (void*)addInt, NULL);
	pthread_join(thread, NULL);
	pthread_join(thread2, NULL);
	return 0;
}