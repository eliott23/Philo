#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

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

void	*achhadlmlawi(void *inf)
{
	printf("am sleeping\n");
	sleep(250);
	return (0);
}
int	main(int ac, char **av)
{
	t_inf		*inf;
	t_inf		temp;
	pthread_t	*t;
	int			i;
	int			count;

	count = 0;
	i = 0;
	if (ac < 5)
		return (0);
	t = malloc(sizeof(pthread_t) * temp.n_philo);
	if (!ft_init(&temp, av, ac) || !t)
		return (0);
	ft_f(&temp);
	printf("this is i %d checking %d bfr and this is the address\
	%p\n", i, (temp.n_eat)[0],&(temp.n_eat)[0]);
	pthread_mutex_lock(&(temp.death_mutex[0]));
	while (i < temp.n_philo)
	{
		inf = malloc(sizeof(t_inf));
		*inf = temp;
		inf->i = i + 1;
		pthread_create(&t[i], NULL, &achhadlmlawi, NULL); // changed the routine and the argument
		//sleep(1);
		printf("checking %d and this is the address\
		%p\n",(temp.n_eat)[0],&(temp.n_eat)[0]);
		i++;
	}
	printf("checking int the end %d and this is the address\
		%p\n",(temp.n_eat)[0],&(temp.n_eat)[0]);
	pthread_mutex_unlock(&(temp.death_mutex[0]));
	/*
	while (i < temp.n_philo)
	if (!(m_helper(*inf, 0, count)))
		return (0);
		*/
}
