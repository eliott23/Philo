#include "philo.h"

typedef struct var{
	int i;
	struct timeval start;
	pthread_mutex_t	*mutex;
	long long		*last_meal;
	int				t_sleep;
	int				t_eat;
	int				t_die;
	int				n_philo;
	int				n_eat;
}t_inf;

long long	get_timestamp(struct timeval start)
{
	struct timeval	t;
	long long		v;

	gettimeofday(&t, NULL);
	v = ((t.tv_sec * 1000000) + t.tv_usec - (start.tv_sec * 1000000) - start.tv_usec) / 1000;
	return (v);
}

void	*test(void *inf)
{
	printf("Hi am philo %d thinking at %lld\n", \
	((t_inf*)inf)->i, get_timestamp(((t_inf*)inf)->start));
	printf("philo %d is eating at %lld\n", \
	((t_inf*)inf)->i, get_timestamp(((t_inf*)inf)->start));
	printf("philo %d is dead at %lld\n", \
	((t_inf*)inf)->i, get_timestamp(((t_inf*)inf)->start));
	free(inf);
	return(0);
}

void	ft_init(t_inf *temp, char **av)
{
	int	i;

	i = 0;
	gettimeofday(&(temp->start),NULL);
	temp->i = 0;
	temp->n_philo = ft_atoi(av[1]);
	temp->t_die = ft_atoi(av[2]);
	temp->t_eat = ft_atoi(av[3]);
	temp->t_sleep = ft_atoi(av[4]);
	temp->mutex = malloc(sizeof(pthread_mutex_t) * (temp->n_philo));
	temp->last_meal = malloc(sizeof(int) * (temp->n_philo));
	memset(temp->last_meal, 0, temp->n_philo * 4);
	while (i < temp->n_philo)
	{
		pthread_mutex_init(&(temp->mutex[i]), NULL);
		i++;
	}
	// temp->n_eat = ft_atoi(av[5]);
}

int	main (int ac, char **av)
{
	t_inf	*inf;
	t_inf	temp;
	int		i;
	pthread_t *t;

	i = 0;
	if (ac < 5)
		return (0);
	ft_init(&temp, av);
	t = malloc(sizeof(pthread_t) * temp.n_philo);
	while (i < temp.n_philo)
	{
		inf = malloc(sizeof(t_inf));
		*inf = temp;
		inf->i = i + 1;
		pthread_create(&t[i],NULL, &test, inf);
		i++;
	}
	i = 0;
	while (i < temp.n_philo)
	{
		pthread_join(t[i],NULL);
		i++;
	}
	printf("%lld\n",get_timestamp(temp.start));
}
