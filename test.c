#include "philo.h"

void	*rou(void *inf)
{
	printf("hh\n");
	sleep(30);
	return (0);
}
int	main()
{
	int	i = 0;
	pthread_t t = malloc(sizeof(pthread_t));
	pthread_create(&t, NULL, &rou, &i);
	printf("this is i now %d\n", i);
}
