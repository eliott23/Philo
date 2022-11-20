#include "philo.h"

typedef struct var{
	int i;
	struct timeval start;
	int	t_sleep;
	int	t_eat;
	int	n_philo;
}t_inf;

long long	get_timestamp(struct timeval start)
{
	struct timeval	t;
	long long		v;

	gettimeofday(&t, NULL);
	v = ((t.tv_sec * 1000000) + t.tv_usec - (start.tv_sec * 1000000) - start.tv_usec) / 1000;
	return (v);
}

void	*test(void *i)
{
	printf("Hi am philo %d\n", *(int*)i);
	printf("philo %d is eating \n",*(int*)i);
	usleep(345 * 1000);
	printf("philo %d is dead \n",*(int*)i);
	free(i);
	return(0);
}

int	main (int ac, char **av)
{
	t_inf	*inf;

	if (ac < 5)
		return (0);
	gettimeofday(&(inf->start),NULL);
	int	n_philo = ft_atoi(av[1]);
	// pthread_t *t = malloc(sizeof(pthread_t) * n_philo);
	// while (i < n_philo)
	// {
	// 	temp = malloc(sizeof(t_inf));
	// 	(*temp).i = i;
	// 	(*temp).start = start;
	// 	pthread_create(&t[i],NULL, &test, temp);
	// 	i++;
	// }
	// i = 0;
	// while (i < n_philo)
	// {
	// 	pthread_join(t[i],NULL);
	// 	i++;
	// }
	get_timestamp(inf->start);
}