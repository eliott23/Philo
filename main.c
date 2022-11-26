#include "philo.h"

typedef struct var{
	int				*d_flag;
	int				i;
	int				my_frk;
	int				othr_frk;
	struct timeval	start;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*death_mutex;
	long long		*last_meal;
	int				t_sleep;
	int				t_eat;
	int				t_die;
	int				n_philo;
	int				*n_eat;
	int				m_eat;
}t_inf;

long long	get_timestamp(struct timeval start)
{
	struct timeval	t;
	long long		v;

	gettimeofday(&t, NULL);
	v = ((t.tv_sec * 1000000) \
			+ t.tv_usec - (start.tv_sec * 1000000) - start.tv_usec) / 1000;
	return (v);
}

void	ft_usleep(long long v, t_inf inf)
{
	long long	i;

	i = get_timestamp(inf.start);
	while (get_timestamp(inf.start) - i < v)
		usleep(250);
}

void	helper(t_inf *inf)
{

}

void	*rout(void *inf)
{
	t_inf	l_inf;

	l_inf = *(t_inf *)inf;
	l_inf.my_frk = l_inf.i - 1;
	if (l_inf.i >= 2)
		l_inf.othr_frk = l_inf.i - 2;
	else
		l_inf.othr_frk = l_inf.n_philo - 1;
	if (!(l_inf.i % 2))
		ft_usleep(1, l_inf);
	pthread_mutex_lock(&(l_inf.death_mutex[l_inf.i - 1]));
	if (l_inf.n_eat)
		l_inf.n_eat[l_inf.i -1] = 0;
	pthread_mutex_unlock(&(l_inf.death_mutex[l_inf.i - 1]));
	while (1)
	{
		pthread_mutex_lock(&(l_inf.death_mutex[l_inf.i - 1]));
		printf("%lld %d is thinking\n", \
		get_timestamp(l_inf.start), l_inf.i);
		pthread_mutex_unlock(&(l_inf.death_mutex[l_inf.i - 1]));
		if (l_inf.n_philo == 1)
		{
			ft_usleep(l_inf.t_die, l_inf);
			*(l_inf.d_flag) = l_inf.i;
			return (0);
		}
		pthread_mutex_lock(&(l_inf.mutex[l_inf.my_frk]));
		pthread_mutex_lock(&(l_inf.death_mutex[l_inf.i - 1]));
		printf("%lld %d has taken his fork\n", \
		get_timestamp(l_inf.start), l_inf.i);
		pthread_mutex_unlock(&(l_inf.death_mutex[l_inf.i - 1]));
		pthread_mutex_lock(&(l_inf.mutex[l_inf.othr_frk]));
		pthread_mutex_lock(&(l_inf.death_mutex[l_inf.i - 1]));
		printf("%lld %d has taken the other fork\n", \
		get_timestamp(l_inf.start), l_inf.i);
		pthread_mutex_unlock(&(l_inf.death_mutex[l_inf.i - 1]));
		pthread_mutex_lock(&(l_inf.death_mutex[l_inf.i - 1]));
		printf("%lld %d is eating\n", \
		get_timestamp(l_inf.start), l_inf.i);
		if (l_inf.n_eat)
			l_inf.n_eat[l_inf.i - 1]++;
		pthread_mutex_unlock(&(l_inf.death_mutex[l_inf.i - 1]));
		ft_usleep(l_inf.t_eat, l_inf);
		pthread_mutex_lock(&(l_inf.death_mutex[l_inf.i - 1]));
		l_inf.last_meal[l_inf.i - 1] = get_timestamp(l_inf.start);
		pthread_mutex_unlock(&(l_inf.death_mutex[l_inf.i - 1]));
		pthread_mutex_unlock(&(l_inf.mutex[l_inf.my_frk]));
		pthread_mutex_unlock(&(l_inf.mutex[l_inf.othr_frk]));
		pthread_mutex_lock(&(l_inf.death_mutex[l_inf.i - 1]));
		printf("%lld %d is sleeping\n", \
		get_timestamp(l_inf.start), l_inf.i);
		pthread_mutex_unlock(&(l_inf.death_mutex[l_inf.i - 1]));
		ft_usleep(l_inf.t_sleep, l_inf);
	}
	free (inf);
	return (0);
}

void	ft_init(t_inf *temp, char **av, int ac)
{
	int	i;

	i = 0;
	gettimeofday(&(temp->start), NULL);
	temp->i = 0;
	temp->n_philo = ft_atoi(av[1]);
	temp->t_die = ft_atoi(av[2]);
	temp->t_eat = ft_atoi(av[3]);
	temp->t_sleep = ft_atoi(av[4]);
	temp->n_eat = malloc(sizeof(int) * (temp->n_philo));
	temp->mutex = malloc(sizeof(pthread_mutex_t) * (temp->n_philo));
	temp->death_mutex = malloc(sizeof(pthread_mutex_t) * (temp->n_philo));
	temp->last_meal = malloc(sizeof(long long) * (temp->n_philo));
	temp->d_flag = malloc(sizeof(int));
	*(temp->d_flag) = 0;
	i = 0;
	while (i < temp->n_philo)
	{
		pthread_mutex_init(&(temp->mutex[i]), NULL);
		pthread_mutex_init(&(temp->death_mutex[i]), NULL);
		i++;
	}
	i = 0;
	while (i < temp->n_philo)
	{
		temp->last_meal[i] = 0;
		i++;
	}
	if (ac > 5)
		temp->m_eat = ft_atoi(av[5]);
	else
		temp->n_eat = NULL;
}

int	main(int ac, char **av)
{
	t_inf		*inf;
	t_inf		temp;
	pthread_t	*t;
	int			i;
	long long	l_meal;
	int			count;

	count = 0;
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
		pthread_create(&t[i], NULL, &rout, inf);
		i++;
	}
	i = 0;
	while (i < temp.n_philo)
	{
		pthread_mutex_lock(&(temp.death_mutex[i]));
		l_meal = temp.last_meal[i];
		if (temp.n_eat && temp.n_eat[i] >= temp.m_eat)
			count++;
		if (pthread_mutex_unlock(&(temp.death_mutex[i])))
			return (0);
		if ((get_timestamp(temp.start) - l_meal) >= temp.t_die)
		{
			while (temp.n_philo)
			{
				pthread_mutex_lock(&(temp.death_mutex[temp.n_philo - 1]));
				(temp.n_philo)--;
			}
			printf("%lld %d died\n", \
			get_timestamp(temp.start), i + 1);
			return (0);
		}
		i++;
		if (count == temp.n_philo)
			return (0);
		else if (i == temp.n_philo)
		{
			i = 0;
			count = 0;
		}
	}
}
