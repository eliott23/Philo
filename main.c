#include "philo.h"

void *get_timestamp(void *i)
{
	printf("Hi am philosopher number %d\n", *(int *)i);
	usleep(70);
	printf("Hi am dead\n");
	return(0);
}

int	main(int ac, char **av)
{
	struct timeval start;
	struct timeval end;
	int	i = 0;
	int	temp;
	int	n_philo = ft_atoi(av[1]);
	pthread_t *t = malloc(sizeof(pthread_t) * n_philo);
	gettimeofday(&start,NULL);
	while (i < n_philo)
	{
		temp = i;
		pthread_create(&t[i],NULL, &get_timestamp, &temp);
		i++;
	}
	i = 0;
	while (i < n_philo)
	{
		pthread_join(t[i],NULL);
		i++;
	}
	gettimeofday(&end,NULL);
	printf("start time = %ld,%d\n",start.tv_sec, start.tv_usec);
	printf("end time = %ld,%d\n",end.tv_sec, end.tv_usec);
}