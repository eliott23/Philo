#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

void	*test()
{
	printf("lol\n");
	return (0);
}

int	main()
{
	pthread_t t;
	
	pthread_create(&t,NULL, &test, NULL);
	pthread_join(t,NULL);
}
