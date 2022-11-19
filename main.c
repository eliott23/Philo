#include "philo.h"

void *get_timestamp()
{
	printf("this is the time\n");
	return(0);
}

int	main(int ac, char **av)
{
	struct timeval start;
	struct timeval end;
	int	i = 0;
	int	n_philo = ft_atoi(av[1]);
	pthread_t *t = malloc(sizeof(pthread_t) * n_philo);
	gettimeofday(&start,NULL);
	while (i < n_philo)
	{
		pthread_create(&t[i],NULL, &get_timestamp, i);
		i++;
	}
	i = 0;
	while (i < n_philo)
	{
		pthread_join(t[i],NULL);
	}
	gettimeofday(&end,NULL);
	printf("start time = %ld,%d\n",start.tv_sec, start.tv_usec);
	printf("end time = %ld,%d\n",end.tv_sec, end.tv_usec);
}