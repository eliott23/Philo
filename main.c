#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

void *get_timestamp()
{
	struct timeval lol;

	gettimeofday(&lol,NULL);
	printf("time = %lld\n",(long long unsigned)lol.tv_sec);
	printf("time usec = %d\n",lol.tv_usec);
	return(0);
}

void	*test()
{
	printf("lol\n");
	return (0);
}

int	main(int ac, char **av)
{
	pthread_t t;
	struct timeval lol;

	gettimeofday(&lol,NULL);
	printf("start time = %ld,%d\n",lol.tv_sec, lol.tv_usec);
	pthread_create(&t,NULL, &get_timestamp, NULL);
	pthread_join(t,NULL);
}