#include "philo.h"

typedef struct var{
	int				i;
	int				my_frk;
	int				othr_frk;
	struct			timeval start;
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

int	is_alive(t_inf inf)
{
	struct timeval t;
	long long		v;

	gettimeofday(&t,NULL);
	v = get_timestamp(inf.start) - inf.last_meal[inf.i];
	if (v < inf.t_die)
		return (1);
	return (0);
}

void	*test(void *inf)
{
	t_inf l_inf = *(t_inf *)inf;
	l_inf.my_frk = l_inf.i - 1;
	if (l_inf.i > 2)
		l_inf.othr_frk = l_inf.i - 2;
	else
		l_inf.othr_frk = l_inf.n_philo - 1;
	while (1)
	{
		printf("%lld %d is thinking\n", \
		get_timestamp(l_inf.start), l_inf.i);
		if (l_inf.n_philo == 1)
		{
			usleep(l_inf.t_die * 1000);
			printf("%lld %d died\n", \
			get_timestamp(l_inf.start), l_inf.i);
			return (0);
		}
		pthread_mutex_lock(&(l_inf.mutex[l_inf.my_frk])); //locked the mutex;
		printf("%lld %d has taken his fork\n", \
		get_timestamp(l_inf.start), l_inf.i);
		pthread_mutex_lock(&(l_inf.mutex[l_inf.othr_frk])); //locked the second mutex
		printf("%lld %d has taken the other fork\n", \
		get_timestamp(l_inf.start), l_inf.i);
		printf("%lld %d is eating\n", \
		get_timestamp(l_inf.start), l_inf.i);
		usleep(l_inf.t_eat * 1000);
		l_inf.last_meal[l_inf.i - 1] = get_timestamp(l_inf.start);
		pthread_mutex_unlock(&(l_inf.mutex[l_inf.my_frk])); //unlcoked the first mutex;
		pthread_mutex_unlock(&(l_inf.mutex[l_inf.othr_frk])); //unlock the second;
		printf("%lld %d is sleeping\n", \
		get_timestamp(l_inf.start), l_inf.i);
		usleep(l_inf.t_sleep * 1000);
	}
	printf("%lld %d died\n", \
	get_timestamp(l_inf.start), l_inf.i);
	free(inf);
	return(0);
}

void	ft_init(t_inf *temp, char **av, int ac)
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
	temp->last_meal = malloc(sizeof(long long) * (temp->n_philo));
	i = 0;
	while (i < temp->n_philo)
	{ 
		printf("fork %d created\n", i);
		pthread_mutex_init(&(temp->mutex[i]), NULL);
		i++;
	}
	// printf("testing\n");
	// if (temp->mutex[i])
		printf("hah\n");
	i = 0;
	while (i < temp->n_philo)
	{
		temp->last_meal[i] = 0;
		i++;
	}
	if (ac > 5)
		temp->n_eat = ft_atoi(av[5]);
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
	ft_init(&temp, av, ac);
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
	i = 0;
	// while (t[i])
	// {
	// 	// printf("checking\n");
	// 	i++;
	// 	if (i == temp.n_philo)
	// 		i = 0;
	// }
}