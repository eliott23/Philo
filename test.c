#include "philo.h"

void	*test(void *arg)
{
	pthread_mutex_lock((pthread_mutex_t *)arg);
	printf("test\n");
	pthread_mutex_unlock((pthread_mutex_t *)arg);
	return (0);
}

int	main(int ac, char **av)
{
	int	n_philo = ft_atoi(av[1]);
	pthread_mutex_t *mutex = malloc(sizeof(pthread_mutex_t) * n_philo);
	pthread_mutex_init(mutex, NULL);
	pthread_mutex_lock(&mutex[1000]);
	int	i = 0;
	pthread_t	*t = malloc(sizeof(pthread_t) * n_philo);
	while (i < n_philo)
	{
		pthread_create(&t[i],NULL, &test, mutex);
		i++;
	}
	pthread_join(t[0],NULL);
}
