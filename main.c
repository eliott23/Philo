#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

void *get_timestamp()
{
	struct timeval lol;

	gettimeofday(&lol,NULL);
	printf("this is the size %ld\n",sizeof(long long unsigned));
	printf("time = %lld\n",(long long unsigned)lol.tv_sec);
	printf("time = %lld\n",(long long unsigned)lol.tv_usec);
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

	pthread_create(&t,NULL, &get_timestamp, NULL);
	pthread_join(t,NULL);
}