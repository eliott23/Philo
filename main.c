#include "philo.h"

void	get_timestamp(struct timeval start)
{
	struct timeval	t;
	long long		v;

	gettimeofday(&t,NULL);
	v = ((t.tv_sec * 1000000) + t.tv_usec - (start.tv_sec * 1000000) - start.tv_usec) / 1000;
	printf("%lld ms since the start of the program\n", v);
}

// void *get_timestamp(void *i)
// {
// 	printf("Hi am philosopher number %d\n", (*(int *)i) + 1);
// 	usleep(70);
// 	printf("Hi am philo %d and am dead\n", (*(int *)i) + 1);
// 	free(i);
// 	return(0);
// }

int	main(int ac, char **av)
{
	struct timeval start;
	gettimeofday(&start,NULL);
	printf("start time = %ld,%d\n",start.tv_sec, start.tv_usec);
	// int	i = 0;
	// int	*temp;
	// usleep(900);
	// if (ac < 5)
	// 	return (0);
	// int	n_philo = ft_atoi(av[1]);
	// pthread_t *t = malloc(sizeof(pthread_t) * n_philo);
	// while (i < n_philo)
	// {
	// 	temp = malloc(sizeof(int));
	// 	*temp = i;
	// 	pthread_create(&t[i],NULL, &get_timestamp, temp);
	// 	i++;
	// }
	// i = 0;
	// while (i < n_philo)
	// {
	// 	pthread_join(t[i],NULL);
	// 	i++;
	// }
	get_timestamp(start);
}