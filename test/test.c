#include "../philo.h"

void	*rou(void *inf)
{
	printf("hh\n");
	sleep(30);
	return (0);
}

int	main()
{
	int	i = 0;
	pthread_t *t = malloc(sizeof(pthread_t) * 5);
	pthread_create(&t[0], NULL, &rou, &i);
	pthread_create(&t[1], NULL, &rou, &i);
	pthread_create(&t[2], NULL, &rou, &i);
	//pthread_create(&t[2], NULL, &rou, &i);
	sleep(5);
	printf("this is i now %d\n", i);
}
