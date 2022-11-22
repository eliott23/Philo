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
	pthread_mutex_t mutex;
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_lock(&mutex);
	int	i = 0;
	int	n_philo = ft_atoi(av[1]);
	pthread_t	*t = malloc(sizeof(pthread_t) * n_philo);
	while (i < n_philo)
	{
		pthread_create(&t[i],NULL, &test, &mutex);
		i++;
	}
	pthread_join(t[i],NULL);
}
